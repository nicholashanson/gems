#include "Blob.h"

// special members
Blob::Blob(){std::fill(floor.begin(), floor.end(), settings::board_height);}
Blob::~Blob(){}

// getters
auto Blob::get_blob() -> blob_t*{return &blob;}
auto Blob::get_floor() const -> floor_t{return floor;}

// stats
auto Blob::count_connectors() const -> count_t {return blob.size();}

auto Blob::count_gems_in_blob() const -> count_t
{
    return std::transform_reduce(blob.cbegin(), blob.cend(), 0, std::plus{},
        []( const connector_t& connector ){
            return connector.size();
    });
}

auto Blob::measure_blob_height() const -> span_t
{
    return *std::max_element(floor.cbegin(), floor.cend());
}

auto Blob::count_gems_to_destroy() const -> count_t
{
    return std::transform_reduce(cbegin(blob), cend(blob), 0, std::plus{},
        [](const connector_t& connector){
            return connector.size() >= settings::gems_to_connect
                                        ? connector.size() : 0;
    });
}

auto Blob::measure_longest_connector() const -> span_t
{
    return std::max_element(blob.cbegin(), blob.cend(),
        [](const connector_t& lhs, const connector_t& rhs){
            return lhs.size() < rhs.size();
    })->size();
}

auto Blob::count_gems_of_color(const color_t color) const -> count_t
{
    return std::transform_reduce(blob.cbegin(), blob.end(), 0, std::plus{},
        [c=color](const connector_t& connector){
            return c == connector.front()->get_color() ? connector.size() : 0;
    });
}

auto Blob::count_connectors_to_destroy() const -> count_t
{
    return std::count_if(blob.cbegin(), blob.cend(), [](const connector_t& connector){
        return connector.size() >= settings::gems_to_connect;
    });
}

auto
Blob::count_gems_to_destroy_of_color(const color_t color) const -> count_t
{
    return std::transform_reduce(cbegin(blob), cend(blob), 0, std::plus{},
        [color=color](const connector_t& connector){
            const bool condition = connector.front()->get_color() ==
                                        color && connector.size() >=
                                        settings::gems_to_connect;
            return condition ? connector.size() : 0;
    });
}

// checkers
auto
Blob::gems_are_adjacent(const gem_raw_ptr first, const gem_raw_ptr second) const -> bool
{
    const bool gems_are_x_adjacent =
        abs( first->get_x() - second->get_x() ) == 1 && first->get_y() == second->get_y();
    const bool gems_are_y_adjacent =
        abs( first->get_y() - second->get_y() ) == 1 && first->get_x() == second->get_x();

    return gems_are_x_adjacent || gems_are_y_adjacent;
}

// actions
auto Blob::clear_blob() -> void{blob.clear();}

auto Blob::update_floor() -> void
{
    std::fill(floor.begin(), floor.end(), settings::board_height);
    for ( const gem_uptr& gem: blob | std::views::join )
        floor[ gem->get_x() ] = std::min( floor [ gem-> get_x() ], gem->get_y() - 1 );
}

auto Blob::destroy_connectors() -> blob_t
{
    blob_t destroyed_connectors;

    auto connectors_to_destroy = std::partition(blob.begin(), blob.end(),
        []( const connector_t& connector ){
            return connector.size() < settings::gems_to_connect;
    });

    std::move( connectors_to_destroy, blob.end(), std::back_inserter( destroyed_connectors ) );

    blob.erase( connectors_to_destroy, blob.end() );

    return destroyed_connectors;
}

auto Blob::add_gem_to_blob(gem_uptr gem) -> void
{
    // indexes of connectors the gem is adjacent to
    std::vector<int> adjacent_connector_indexes;

    // the index of connectors in the blob
    int index = 0;

    for ( connector_t& connector : blob ){

        // the color of the gem to add is the same as the color of the gems
        // in this connector
        bool colors_match = connector.front()->get_color() == gem->get_color();

        if ( colors_match )
            for ( gem_uptr& connector_gem : connector )
                // colors match, now test if the gem is adjacent to any
                // of the gems in this connector
                if ( gems_are_adjacent( gem.get(), connector_gem.get() ) ) {
                    adjacent_connector_indexes.push_back( index );
                    break;
                }

        // move to next connector
        index++;
    }

    // the gem is a adjacent to one or more connectors
    if ( !adjacent_connector_indexes.empty() ) {

        int destination_connector_index = adjacent_connector_indexes.front();

        // add gem to the first adjacent connector
        blob [ destination_connector_index ].push_back( std::move( gem ) );

        // merge connected connectors
        std::for_each( std::next(adjacent_connector_indexes.begin()), adjacent_connector_indexes.end(),
            [&]( const int& connector_to_splice_index ){
                // list splice is constant time and won't
                // move elements in memory
                blob[ destination_connector_index ].splice(
                blob[ destination_connector_index ].begin(),
                blob[ connector_to_splice_index ],
                blob[ connector_to_splice_index ].begin(),
                blob[ connector_to_splice_index ].end() );
                // remove the empty connector
                blob.erase( blob.begin() + connector_to_splice_index );
        });

    } else { // no matching connector, make a new one
        connector_t temp;
        temp.push_back( std::move(gem) );
        blob.push_back( std::move(temp) );
    }
}


























