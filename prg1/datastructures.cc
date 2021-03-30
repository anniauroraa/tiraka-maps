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

    std::list<long>::iterator i = places_list_.begin();
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
    if ( areas_.find(id1) == areas_.end() || areas_.find(id2) == areas_.end()) {
        return NO_AREA;
    }

    std::vector<AreaID> areas1 = subarea_in_areas(id1);
    std::vector<AreaID> areas2 = subarea_in_areas(id2);

    int index;
    if ( areas1.size() <= areas2.size() ) index = areas1.size()-1;
    else index = areas2.size()-1;

    // Check that areas have the same root
    if ( areas1[areas1.size()-1] != areas2[areas2.size()-1] ) {
        return NO_AREA;
    }

    AreaID common_area = areas1[areas1.size()-1];
    while ( index >= 0 ) {
        if ( areas1[index] == areas2[index] ) {
            common_area = areas1[index];
        }
        index--;
    }

    return common_area;
}


