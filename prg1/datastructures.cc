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
    // Replace this comment with your implementation
}

int Datastructures::place_count()
{
    // Replace this comment with your implementation
    return 0;
}

void Datastructures::clear_all()
{
    // Replace this comment with your implementation
}

std::vector<PlaceID> Datastructures::all_places()
{
    places_list_.clear();

    for ( auto const& place : places_ ) {                   // O(n)
        places_list_.push_back( place.first );
    }
    return places_list_;
}

bool Datastructures::add_place(PlaceID id, const Name& name, PlaceType type, Coord xy)
{
    if ( places_.find(id) == places_.end() ) {              // O(n)
        Place new_struct = {name, type, xy};
        places_.insert({id, new_struct});                   // O(1)

        return true;
    }
    return false;
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
    // Replace this comment with your implementation
    return false;
}

Name Datastructures::get_area_name(AreaID id)
{
    // Replace this comment with your implementation
    return NO_NAME;
}

std::vector<Coord> Datastructures::get_area_coords(AreaID id)
{
    // Replace this comment with your implementation
    return {NO_COORD};
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
    std::copy(places_.begin(), places_.end(),                   // O(n)
              std::back_inserter(place_pairs));

    //Create sorted list containing pairs
    std::sort(place_pairs.begin(), place_pairs.end(),           // O(n log n)
                [](const std::pair<PlaceID, Place>& l,
                   const std::pair<PlaceID, Place>& r) {
                    if (l.second.name != r.second.name)
                        return l.second.name < r.second.name;

                    return l.first < r.first;
                });

    places_list_.clear();                                       // O(1)
    for ( auto const& place : place_pairs ) {                   // O(n)
       places_list_.push_back(place.first);                     // O(1)
    }

    return places_list_;
}

std::vector<PlaceID> Datastructures::places_coord_order()
{
    std::vector<std::pair<PlaceID, Place>> place_pairs;
    std::copy(places_.begin(), places_.end(), std::back_inserter(place_pairs));

    //Create sorted list containing pairs
    std::sort(place_pairs.begin(), place_pairs.end(),
                [](const std::pair<PlaceID, Place>& l,
                   const std::pair<PlaceID, Place>& r) {
                    if (l.second.xy != r.second.xy)
                        return l.second.xy < r.second.xy;

                    return l.first < r.first;
                });

    places_list_.clear();
    for ( auto const& place : place_pairs ) {
       places_list_.push_back(place.first);
    }

    return places_list_;
}

std::vector<PlaceID> Datastructures::find_places_name(Name const& name)
{
    places_list_.clear();

    for ( auto place : places_ ) {                          // O(n)
        if ( place.second.name == name ) {
            places_list_.push_back(place.first);            // O(1)
        }
    }

    return places_list_;
}

std::vector<PlaceID> Datastructures::find_places_type(PlaceType type)
{
    places_list_.clear();

    for ( auto place : places_ ) {
        if ( place.second.type == type ) {
            places_list_.push_back(place.first);
        }
    }

    return places_list_;
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
    // Replace this comment with your implementation
    return {};
}

bool Datastructures::add_subarea_to_area(AreaID id, AreaID parentid)
{
    // Replace this comment with your implementation
    return false;
}

std::vector<AreaID> Datastructures::subarea_in_areas(AreaID id)
{
    // Replace this comment with your implementation
    return {NO_AREA};
}

std::vector<PlaceID> Datastructures::places_closest_to(Coord xy, PlaceType type)
{
    // Replace this comment with your implementation
    return {};
}

bool Datastructures::remove_place(PlaceID id)
{
    // Replace this comment with your implementation
    return false;
}

std::vector<AreaID> Datastructures::all_subareas_in_area(AreaID id)
{
    // Replace this comment with your implementation
    return {NO_AREA};
}

AreaID Datastructures::common_area_of_subareas(AreaID id1, AreaID id2)
{
    // Replace this comment with your implementation
    return NO_AREA;
}
