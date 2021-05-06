// Datastructures.cc

#include "datastructures.hh"

#include <random>

#include <cmath>

std::minstd_rand rand_engine; // Reasonably quick pseudo-random generator

template <typename Type>
Type random_in_range(Type start, Type end)
{
    auto range = end-start;
    ++range;

    auto num = std::uniform_int_distribution<unsigned long int>(0, range-1)(rand_engine);

    return static_cast<Type>(start+num);
}

// Modify the code below to implement the functionality of the class.
// Also remove comments from the parameter names when you implement
// an operation (Commenting out parameter name prevents compiler from
// warning about unused parameters on operations you haven't yet implemented.)

Datastructures::Datastructures()
{
    // Replace this comment with your implementation
}

Datastructures::~Datastructures()
{
    clear_all();
}

int Datastructures::place_count()
{
    return places_list_.size();
}

void Datastructures::clear_all()
{
    places_list_.clear();
    places_.clear();

    areas_list_.clear();
    areas_.clear();
    subareas_.clear();

    ways_.clear();
    crossroads_.clear();
    route_.clear();
    sum_distance_ = 0;
}

std::vector<PlaceID> Datastructures::all_places()
{
    std::vector<PlaceID> all_places;

    for ( PlaceID id : places_list_ ) {                     // O(n)
        all_places.push_back(id);
    }

    return all_places;
}

bool Datastructures::add_place(PlaceID id, const Name& name, PlaceType type, Coord xy)
{
    if ( places_.find(id) != places_.end() ) {              // O(n)
        return false;
    }
    Place new_struct = {name, type, xy};
    places_.insert({id, new_struct});                       // O(1)

    places_list_.push_back(id);

    return true;
}

std::pair<Name, PlaceType> Datastructures::get_place_name_type(PlaceID id)
{
    if ( places_.find(id) == places_.end() ) {              // O(n)
         return {NO_NAME, PlaceType::NO_TYPE};
    }
    return {places_[id].name, places_[id].type };           // O(n)
}

Coord Datastructures::get_place_coord(PlaceID id)
{
    if ( places_.find(id) == places_.end() ) {              // O(n)
        return NO_COORD;
    }
    return places_[id].xy;                                  // O(n)
}

bool Datastructures::add_area(AreaID id, const Name &name, std::vector<Coord> coords)
{
    if ( areas_.find(id) == areas_.end() ) {
        Area new_struct = {id, name, coords, nullptr, {}};
        areas_.insert({id, new_struct});
        areas_list_.push_back(id);
        return true;
    }
    return false;
}

Name Datastructures::get_area_name(AreaID id)
{
    if ( areas_.find(id) == areas_.end() ) {                 // O(n)
         return NO_NAME;
    }
    return areas_[id].name;
}

std::vector<Coord> Datastructures::get_area_coords(AreaID id)
{
    if ( areas_.find(id) == areas_.end() ) {
        return {NO_COORD};
    }
    return areas_[id].shape;
}

void Datastructures::creation_finished()
{
    // Replace this comment with your implementation
    // NOTE!! It's quite ok to leave this empty, if you don't need operations
    // that are performed after all additions have been done.
}

std::vector<PlaceID> Datastructures::places_alphabetically()
{
    std::vector<std::pair<PlaceID, Place>> place_pairs;
    std::copy(places_.begin(), places_.end(),                    // O(n)
              std::back_inserter(place_pairs));

    //Create sorted list containing pairs
    std::sort(place_pairs.begin(), place_pairs.end(),           // O(n log n)
                [](const std::pair<PlaceID, Place>& l,
                   const std::pair<PlaceID, Place>& r) {
                    if (l.second.name != r.second.name)
                        return l.second.name < r.second.name;

                    return l.first < r.first;
                });

    std::vector<PlaceID> alphabetical_list;                     // O(1)
    for ( auto const& place : place_pairs ) {                   // O(n)
       alphabetical_list.push_back(place.first);                // O(1)
    }

    return alphabetical_list;
}

std::vector<PlaceID> Datastructures::places_coord_order()
{
    std::vector<std::pair<PlaceID, Place>> place_pairs;
    std::copy(places_.begin(), places_.end(), std::back_inserter(place_pairs));

    //Create sorted list containing pairs
    std::sort(place_pairs.begin(), place_pairs.end(),
                [](const std::pair<PlaceID, Place>& pair1,
                   const std::pair<PlaceID, Place>& pair2) {
                    Coord coord1 = pair1.second.xy;
                    Coord coord2 = pair2.second.xy;

                    if ( coord1 != coord2 ) {
                        return (sqrt(pow(coord1.x,2)+pow(coord1.y,2))
                                 < sqrt(pow(coord2.x,2)+pow(coord2.y,2)));
                    }
                    return pair1.first < pair2.first;
                });

    std::vector<PlaceID> right_order;
    for ( auto const& place : place_pairs ) {
       right_order.push_back(place.first);
    }

    return right_order;
}

std::vector<PlaceID> Datastructures::find_places_name(Name const& name)
{
    std::vector<PlaceID> names;

    for ( auto place : places_ ) {                          // O(n)
        if ( place.second.name == name ) {
            names.push_back(place.first);                   // O(1)
        }
    }

    return names;
}

std::vector<PlaceID> Datastructures::find_places_type(PlaceType type)
{
    std::vector<PlaceID> types;

    for ( auto place : places_ ) {
        if ( place.second.type == type ) {
            types.push_back(place.first);
        }
    }

    return types;
}

bool Datastructures::change_place_name(PlaceID id, const Name& newname)
{
    if ( places_.find(id) == places_.end() ) { return false; }  // O(n)

    places_[id].name = newname;                                 // O(n)
    return true;
}

bool Datastructures::change_place_coord(PlaceID id, Coord newcoord)
{
    if ( places_.find(id) == places_.end() ) { return false; }

    places_[id].xy = newcoord;
    return true;
}

std::vector<AreaID> Datastructures::all_areas()
{
    return areas_list_;
}

bool Datastructures::add_subarea_to_area(AreaID id, AreaID parentid)
{
    if ( areas_.find(id) == areas_.end() || areas_.find(parentid) == areas_.end() ) {
        return false;
    }
    else if ( areas_[id].parent != nullptr ) {
        return false;
    }
    areas_[id].parent = &areas_[parentid];
    areas_[parentid].children.push_back(id);

    return true;
}

std::vector<AreaID> Datastructures::subarea_in_areas(AreaID id)
{
    std::vector<AreaID> areas;

    if ( areas_.find(id) == areas_.end() ) {
        return {NO_AREA};
    }
    else if ( areas_[id].parent == nullptr ) {
        return {};
    }

    struct Area *current_parent = areas_[id].parent;

    while ( current_parent != nullptr ) {
        areas.push_back(current_parent->id);
        current_parent = current_parent->parent;
    }

    return areas;
}

std::vector<PlaceID> Datastructures::places_closest_to(Coord xy, PlaceType type)
{
    // Replace this comment with your implementation
    return {};
}

bool Datastructures::remove_place(PlaceID id)
{
    if ( places_.find(id) == places_.end() ) {
        return false;
    }

    places_.erase(id);

    std::list<long long>::iterator i = places_list_.begin();
    for ( PlaceID current_id : places_list_ ) {             // O(n)
        if ( current_id == id ) {
            places_list_.erase(i);                          // O(1)
        }
        i++;
    }
    return true;
}

std::vector<AreaID> Datastructures::all_subareas_in_area(AreaID id)
{
    subareas_.clear();

    if ( areas_.find(id) == areas_.end() ) {
        return {NO_AREA};
    }

    check_children(id);

    return subareas_;
}

void Datastructures::check_children(AreaID id)
{
    std::vector<AreaID> current_children = areas_[id].children;

    if ( current_children.size() == 0 ) {
        return;
    }

    subareas_.insert(subareas_.end(), current_children.begin(), current_children.end());

    for ( auto child : current_children ) {
        check_children(child);
    }
}

AreaID Datastructures::common_area_of_subareas(AreaID id1, AreaID id2)
{
    if ( areas_.find(id1) == areas_.end() || areas_.find(id2) == areas_.end()) { return NO_AREA; }

    auto areas1 = subarea_in_areas(id1);
    auto areas2 = subarea_in_areas(id2);

    if ( areas1.size() == 0 || areas2.size() == 0 ) { return NO_AREA; }

    int index;
    if ( areas1.size() <= areas2.size() ) index = areas1.size()-1;
    else index = areas2.size()-1;

    // Check that areas have the same root
    if ( areas1.back() != areas2.back() ) { return NO_AREA; }

    AreaID common_area = areas1.back();
    while ( index >= 0 ) {
        if ( areas1[index] == areas2[index] ) {
            common_area = areas1[index];
            index--;
        }
        else { break; }
    }

    return common_area;
}


std::vector<WayID> Datastructures::all_ways()
{
    std::vector<WayID> all_ways;

    for ( auto pair : ways_ ) {
        all_ways.push_back(pair.first);
    }

    return all_ways;
}

bool Datastructures::add_way(WayID id, std::vector<Coord> coords)
{   
    if ( ways_.find(id) != ways_.end() ) {
        return false;
    }

    Coord first_coord = coords[0]; Coord last_coord = coords.back();

    Way new_way = { id, coords };
    ways_.insert({id, new_way});


    // Create new crossroad if needed
    if ( crossroads_.find(first_coord) == crossroads_.end() ) {

        Crossroad first_crossroad = { first_coord, {}, WHITE, NO_DISTANCE ,nullptr };
        crossroads_.insert({first_coord, first_crossroad});
    }

    // Create new crossroad if needed
    if ( crossroads_.find(last_coord) == crossroads_.end() ) {

        Crossroad second_crossroad = { last_coord, {}, WHITE, NO_DISTANCE ,nullptr };
        crossroads_.insert({last_coord, second_crossroad});
    }

    // Give one connection for both crossroads
    crossroads_[first_coord].connections.push_back({&crossroads_[last_coord], &ways_[id]});
    crossroads_[last_coord].connections.push_back({&crossroads_[first_coord], &ways_[id]});

    return true;
}

std::vector<std::pair<WayID, Coord>> Datastructures::ways_from(Coord xy)
{
    std::vector<std::pair<WayID, Coord>> nearby_crossroads = {};

    if ( crossroads_.find(xy) == crossroads_.end() ) {
        return {{NO_WAY, NO_COORD}};
    }

    for ( const auto &pair : crossroads_[xy].connections ) {
        nearby_crossroads.push_back({pair.second->id, pair.first->coordinate});
    }

    return nearby_crossroads;
}

std::vector<Coord> Datastructures::get_way_coords(WayID id)
{
    if ( ways_.find(id) == ways_.end() ) { return {NO_COORD}; }

    return ways_[id].coords;
}

void Datastructures::clear_ways()
{
    ways_.clear();
    crossroads_.clear();
}

std::vector<std::tuple<Coord, WayID, Distance> > Datastructures::route_any(Coord fromxy, Coord toxy)
{
    if ( crossroads_.find(fromxy) == crossroads_.end() ||
         crossroads_.find(toxy) == crossroads_.end() ) {
        return {{NO_COORD, NO_WAY, NO_DISTANCE}};
    }

    route_.clear();
    clear_crossroads();
    sum_distance_ = 0;
    bool destination_found = false;

    std::queue<Crossroad*> paths;

    crossroads_[toxy].state = GREY;
    paths.push(&crossroads_[toxy]);

    // BFS algorithm
    while ( paths.size() > 0 && destination_found == false ) {

        Crossroad* current = paths.front();
        paths.pop();

        for ( auto& neighbor : current->connections ) {

            if ( neighbor.first->state == WHITE ) {

                // Check if this is the destination
                if ( neighbor.first->coordinate == fromxy ) {
                    destination_found = true;
                }

                neighbor.first->state = GREY;
                neighbor.first->previous = current;

                current->distance = distBetween(neighbor.first->coordinate, current->coordinate);
                paths.push(neighbor.first);
            }
        }
        current->state = BLACK;
    }

    if ( destination_found == true ) {
        find_the_path(paths, &crossroads_[toxy], &crossroads_[fromxy]);
    }

    if ( route_.size() == 0 ){
        return {};
    }

    return route_;
}

void Datastructures::find_the_path(std::queue<Crossroad*> paths, Crossroad *end, Crossroad *current)
{
    if ( current == end ) {
        sum_distance_ += current->distance;
        route_.push_back({ current->coordinate, NO_WAY, sum_distance_ });
        return;
    }
    else if ( current->previous == nullptr ) { return; }
    else {
        if ( route_.size() == 0 )   { sum_distance_ = 0; }
        else                        { sum_distance_ += current->distance; }

        route_.push_back({ current->coordinate, NO_WAY, sum_distance_ });
        find_the_path(paths, end, current->previous);
    }
}

void Datastructures::clear_crossroads()
{
    for ( auto& crossroad : crossroads_ ) {
        crossroad.second.state = WHITE;
        crossroad.second.distance = NO_DISTANCE;
        crossroad.second.previous = nullptr;
    }
}

int Datastructures::distBetween(Coord coord1, Coord coord2)
{
    return floor(sqrt(pow((coord1.x - coord2.x), 2) + pow((coord1.y - coord2.y), 2)));
}

bool Datastructures::remove_way(WayID id)
{
    // Replace this comment with your implementation
    return false;
}

std::vector<std::tuple<Coord, WayID, Distance> > Datastructures::route_least_crossroads(Coord fromxy, Coord toxy)
{
    // Replace this comment with your implementation
    return {{NO_COORD, NO_WAY, NO_DISTANCE}};
}

std::vector<std::tuple<Coord, WayID> > Datastructures::route_with_cycle(Coord fromxy)
{
    // Replace this comment with your implementation
    return {{NO_COORD, NO_WAY}};
}

std::vector<std::tuple<Coord, WayID, Distance> > Datastructures::route_shortest_distance(Coord fromxy, Coord toxy)
{
    // Replace this comment with your implementation
    return {{NO_COORD, NO_WAY, NO_DISTANCE}};
}

Distance Datastructures::trim_ways()
{
    // Replace this comment with your implementation
    return NO_DISTANCE;
}
