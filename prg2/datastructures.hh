// Datastructures.hh

#ifndef DATASTRUCTURES_HH
#define DATASTRUCTURES_HH

#include <string>
#include <vector>
#include <tuple>
#include <utility>
#include <limits>
#include <functional>
#include <unordered_map>
#include <algorithm>
#include <list>
#include <queue>
#include <iterator>

#include <QDebug>


// Types for IDs
using PlaceID = long long int;
using AreaID = long long int;
using Name = std::string;
using WayID = std::string;

// Return values for cases where required thing was not found
PlaceID const NO_PLACE = -1;
AreaID const NO_AREA = -1;
WayID const NO_WAY = "!!No way!!";

// Return value for cases where integer values were not found
int const NO_VALUE = std::numeric_limits<int>::min();

// Return value for cases where name values were not found
Name const NO_NAME = "!!NO_NAME!!";

// Enumeration for different place types
// !!Note since this is a C++11 "scoped enumeration", you'll have to refer to
// individual values as PlaceType::SHELTER etc.
enum class PlaceType { OTHER=0, FIREPIT, SHELTER, PARKING, PEAK, BAY, AREA, NO_TYPE };

// Type for a coordinate (x, y)
struct Coord
{
    int x = NO_VALUE;
    int y = NO_VALUE;
};

// Example: Defining == and hash function for Coord so that it can be used
// as key for std::unordered_map/set, if needed
inline bool operator==(Coord c1, Coord c2) { return c1.x == c2.x && c1.y == c2.y; }
inline bool operator!=(Coord c1, Coord c2) { return !(c1==c2); } // Not strictly necessary

struct CoordHash
{
    std::size_t operator()(Coord xy) const
    {
        auto hasher = std::hash<int>();
        auto xhash = hasher(xy.x);
        auto yhash = hasher(xy.y);
        // Combine hash values (magic!)
        return xhash ^ (yhash + 0x9e3779b9 + (xhash << 6) + (xhash >> 2));
    }
};

// Example: Defining < for Coord so that it can be used
// as key for std::map/set
inline bool operator<(Coord c1, Coord c2)
{
    if (c1.y < c2.y) { return true; }
    else if (c2.y < c1.y) { return false; }
    else { return c1.x < c2.x; }
}

// Return value for cases where coordinates were not found
Coord const NO_COORD = {NO_VALUE, NO_VALUE};

// Type for a distance (in metres)
using Distance = int;

// Return value for cases where Duration is unknown
Distance const NO_DISTANCE = NO_VALUE;

// This is the class you are supposed to implement

class Datastructures
{
public:
    Datastructures();
    ~Datastructures();

    // Estimate of performance: O(1)
    // Short rationale for estimate: Performance doesn't change in relation
    // to the size of the data
    int place_count();

    // Estimate of performance: O(1)
    // Short rationale for estimate: Performance doesn't change in relation
    // to the size of the data
    void clear_all();

    // Estimate of performance: O(n)
    // Short rationale for estimate: for-loop is the heaviest part and it's
    // efficiency is linear
    std::vector<PlaceID> all_places();

    // Estimate of performance: O(n) ≈ Θ(1)
    // Short rationale for estimate: Finding the right index in unordered map is
    // the heaviest part and it's efficiency is constant in average but linear
    // in worst case
    bool add_place(PlaceID id, Name const& name, PlaceType type, Coord xy);

    // Estimate of performance: O(n) ≈ Θ(1)
    // Short rationale for estimate: Finding the right index in unordered map is
    // the heaviest part and it's efficiency is constant in average but linear
    // in worst case
    std::pair<Name, PlaceType> get_place_name_type(PlaceID id);

    // Estimate of performance: O(n) ≈ Θ(1)
    // Short rationale for estimate: Finding the right index in unordered map is
    // the heaviest part and it's efficiency is constant in average but linear
    // in worst case
    Coord get_place_coord(PlaceID id);

    // We recommend you implement the operations below only after implementing the ones above

    // Estimate of performance: O(n log n)
    // Short rationale for estimate: std::sort is the heaviest and it's
    // performance is that much (includes the sorting method which is constant)
    std::vector<PlaceID> places_alphabetically();

    // Estimate of performance: O(n log n)
    // Short rationale for estimate: std::sort is the heaviest and it's
    // performance is that much because the sorting method stays constant
    std::vector<PlaceID> places_coord_order();

    // Estimate of performance: O(n)
    // Short rationale for estimate: for-loop is the heaviest and it's
    // performance is linear
    std::vector<PlaceID> find_places_name(Name const& name);

    // Estimate of performance: O(n)
    // Short rationale for estimate: for-loop is the heaviest and it's
    // performance is linear
    std::vector<PlaceID> find_places_type(PlaceType type);

    // Estimate of performance: O(n) ≈ Θ(1)
    // Short rationale for estimate: Finding the right index in unordered map is
    // the heaviest part and it's efficiency is constant in average but linear
    // in worst case
    bool change_place_name(PlaceID id, Name const& newname);

    // Estimate of performance: O(n) ≈ Θ(1)
    // Short rationale for estimate: Finding the right index in unordered map is
    // the heaviest part and it's efficiency is constant in average but linear
    // in worst case
    bool change_place_coord(PlaceID id, Coord newcoord);

    // We recommend you implement the operations below only after implementing the ones above

    // Estimate of performance: O(n) ≈ Θ(1)
    // Short rationale for estimate: Finding the right index in unordered map is
    // the heaviest part and it's consumption is constant in average but linear
    // in worst case
    bool add_area(AreaID id, Name const& name, std::vector<Coord> coords);

    // Estimate of performance: O(n) ≈ Θ(1)
    // Short rationale for estimate: Finding the right index in unordered map is
    // the heaviest part and it's efficiency is constant in average but linear
    // in worst case
    Name get_area_name(AreaID id);

    // Estimate of performance: O(n) ≈ Θ(1)
    // Short rationale for estimate: Finding the right index in unordered map is
    // the heaviest part and it's efficiency is constant in average but linear
    // in worst case
    std::vector<Coord> get_area_coords(AreaID id);

    // Estimate of performance: O(1)
    // Short rationale for estimate: Performance stays constant. Function
    // only returns a list
    std::vector<AreaID> all_areas();

    // Estimate of performance: O(n) ≈ Θ(1)
    // Short rationale for estimate: Consumption is a sum of linear tasks
    // so the asymptotic performance is linear in worst case. Average
    // performance is close to constant
    bool add_subarea_to_area(AreaID id, AreaID parentid);

    // Estimate of performance: O(n) ≈ Θ(1)
    // Short rationale for estimate: While-loop or finding the right index is
    // the heaviest and it's performance is linear in worst case. Inside the
    // loop everything stays constant. On average the performance is close to constant.
    std::vector<AreaID> subarea_in_areas(AreaID id);

    // Non-compulsory operations

    // Estimate of performance:
    // Short rationale for estimate:
    void creation_finished();

    // Estimate of performance: Θ(n)
    // Short rationale for estimate: function uses recursion and it's time
    // consumption is linear. Recursive algorithm will call itself maximum of n times.
    std::vector<AreaID> all_subareas_in_area(AreaID id);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<PlaceID> places_closest_to(Coord xy, PlaceType type);

    // Estimate of performance: O(n)
    // Short rationale for estimate: Performance of the for-loop and removing an
    // item is linear because removing an item of std::list is constant and
    // for-loop's performance is linear
    bool remove_place(PlaceID id);

    // Estimate of performance: O(n) ≈ Θ(n)
    // Short rationale for estimate: Estimate comes from subarea_in_areas(AreaID id)
    // because it is used in this function and it is the heaviest part of the algorithm.
    AreaID common_area_of_subareas(AreaID id1, AreaID id2);

    // Phase 2 operations

    // Estimate of performance: O(n)
    // Short rationale for estimate: For loop makes it's performance linear
    std::vector<WayID> all_ways();

    // Estimate of performance: O(n) ≈ Θ(1)
    // Short rationale for estimate: Everything is constant but finding the right
    // index from unordered_map is linear in worst case but constant on average
    // Also uses calculate_distance() so it might make this function linear too
    bool add_way(WayID id, std::vector<Coord> coords);

    // Estimate of performance:O(n) ≈ Θ(1)
    // Short rationale for estimate: Everything is constant but finding the right
    // index from unordered_map is linear in worst case but constant on average.
    // For loop is also linear at worst case but in practice it never goes through n amount of data
    std::vector<std::pair<WayID, Coord>> ways_from(Coord xy);

    // Estimate of performance: O(n) ≈ Θ(1)
    // Short rationale for estimate: Everything is constant but finding the right
    // index from unordered_map is linear in worst case but constant on average
    std::vector<Coord> get_way_coords(WayID id);

    // Estimate of performance: O(1)
    // Short rationale for estimate: .clear() operation is constant
    void clear_ways();

    // Estimate of performance: O(n^2) ≈ Θ(n)
    // Short rationale for estimate: Functon uses breadth_first(). There's for loop
    // nested in while loop so the worst case is exponential. Usually
    // the nested for loop is never really heavy (because there is only few connections per crossroad)
    // so in practice the nested for loop doesn't affect the performance and so it is
    // linear on average. linear performance comes from private function clear_crossroads().
    std::vector<std::tuple<Coord, WayID, Distance>> route_any(Coord fromxy, Coord toxy);

    // Non-compulsory operations

    // Estimate of performance: O(n^2) ≈ Θ(n)
    // Short rationale for estimate: Finding the right index in a for loop makes
    // the worst case exponential. Finding the right index from unordered_map
    // is constant on average so the average performance of the function is linear
    bool remove_way(WayID id);

    // Estimate of performance: O(n^2) ≈ Θ(n)
    // Short rationale for estimate: Functon uses breadth_first(). There's for loop
    // nested in while loop so the worst case is exponential. Usually
    // the nested for loop is never really heavy (because there is only few connections per crossroad)
    // so in practice the nested for loop doesn't affect the performance and so it is
    // linear on average. linear performance comes from private function clear_crossroads().
    std::vector<std::tuple<Coord, WayID, Distance>> route_least_crossroads(Coord fromxy, Coord toxy);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<std::tuple<Coord, WayID>> route_with_cycle(Coord fromxy);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<std::tuple<Coord, WayID, Distance>> route_shortest_distance(Coord fromxy, Coord toxy);

    // Estimate of performance:
    // Short rationale for estimate:
    Distance trim_ways();

private:

    // Phase 1

    void check_children(AreaID id);

    struct Place {
        Name name = NO_NAME;
        PlaceType type = PlaceType::NO_TYPE;
        Coord xy;
    };

    std::unordered_map<PlaceID, Place> places_;
    std::list<PlaceID> places_list_;

    struct Area {
        AreaID id = NO_AREA;
        Name name = NO_NAME;
        std::vector<Coord> shape;

        struct Area* parent = nullptr;
        std::vector<AreaID> children;
    };

    std::unordered_map<AreaID, Area> areas_;
    std::vector<AreaID> areas_list_;

    std::vector<AreaID> subareas_;

    // Phase 2

    enum node { WHITE, GREY, BLACK }; // not found, found, processed

    struct Way {
        WayID id = NO_WAY;
        std::vector<Coord> coords;
        Distance d = NO_DISTANCE;
    };

    std::unordered_map<WayID, Way> ways_;

    struct Crossroad {
        Coord coordinate;
        std::vector<std::pair<Crossroad*, Way*>> connections;

        node state = WHITE;
        Crossroad* next = nullptr;
        Way* temp_way = nullptr;
    };

    std::unordered_map<Coord, Crossroad, CoordHash> crossroads_;
    std::vector<std::tuple<Coord, WayID, Distance>> route_;
    Distance sum_distance_ = 0;

    // Estimate of performance: O(n^2) ≈ Θ(n)
    // Short rationale for estimate: There's for loop nested in while loop so the worst
    // case is exponential. Usually the nested for loop is never really heavy
    // (because there is only few connections per crossroad)
    // so in practice the nested for loop doesn't affect the performance and so it is
    // linear on average. linear performance comes from private function clear_crossroads().
    bool breadth_first(Coord fromxy, Coord toxy);

    // Estimate of performance: O(n)
    // Short rationale for estimate: Goes through n amount of data recursively
    void find_the_path(Crossroad* toxy, Crossroad* current);

    // Estimate of performance: O(n)
    // Short rationale for estimate: Goes through for loop
    void clear_crossroads();

    // Estimate of performance: O(n)
    // Short rationale for estimate: For loop makes the function linear compared
    // to the data it receives.
    Distance calculate_distance(std::vector<Coord>);

};

#endif // DATASTRUCTURES_HH
