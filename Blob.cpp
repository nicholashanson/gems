#include "Blob.h"

Blob::Blob()
{
    std::fill(begin(floor), end(floor), settings::board_height);
}

Blob::~Blob()
{

}

floor_t Blob::get_floor()
{
    return this->floor;
}

void Blob::calculate_floor()
{
    for (int i = 0; i < this->floor.size(); i++)
        this->floor[i] = *(this->board[i].begin());
}

/*
int Blob::get_top_of_column(column_t column)
{
    for (auto y: column)
        if (y != 0)
}
*/

void Blob::add_gem_to_blob(gem_uptr gem)
{
    // indexes of connectors the gem is adjacent to
    std::vector<int> matched_connectors;

    // the index of connectors in the blob
    int index = 0;

    for (auto& connector : blob){

        bool colors_match = connector.front()->get_color() == gem->get_color();

        if (colors_match)
            for (auto& connector_gem: connector)
                if (gems_are_connected(gem.get(), connector_gem.get())) {
                    matched_connectors.push_back(index);
                    break;
                }

        index++;
    }

    // the gem is a neighbor of one or more connectors
    if ( !matched_connectors.empty() ) {

        int destination_connector_index = matched_connectors.front();

        // add gem to connector
        blob [ destination_connector_index ].push_back(std::move(gem));

        // merge connected connectors
        std::for_each(std::next(matched_connectors.begin()), matched_connectors.end(),
            [&](const int& connector_to_splice){
                // list splice is constant time
                blob[ destination_connector_index ].splice(
                blob[ destination_connector_index].begin(),
                blob[ connector_to_splice],
                blob[ connector_to_splice].begin(),
                blob[ connector_to_splice].end());
        });

    } else { // no matching connector, make a new one
        connector_t temp;
        temp.push_back( std::move(gem) );
        blob.push_back( std::move(temp) );
    }
}
/*

        blob.push_back( std::vector<Gem>{gem} );

        // merge connectors
        for (; i < matched_connectors.size(); i++) {

            // index of connector to merge
            source_connector_index = matched_connectors[i];

            // insert contents of connector into destination connector
            blob[ destination_connector_index ].insert(
                blob[ destination_connector_index ].begin(),
                blob[ destination_connector_index ].end(),
                blob[ source_connector_index ].begin()
            );

            // delete merged connector
            blob.erase( blob.begin() + matched_connectors[i] - 1 );
        }
    } else // if a matching connector wasn't found, make a new one
        blob.push_back( std::vector<Gem>{gem} );
}

auto Blob::destroy_connectors(void) -> connector_t
{
    std::vector<Gem> deleted_gems;

    int i = 0;
    for (; i < blob.size(); i++)
    {
        int connector_index = i;
        int connector_size = blob[connector_index].size();

        if ( connector_size > 3 )
        {
            deleted_gems = std::move( blob[ connector_index ] );
            blob.erase( blob.begin() + connector_index );
            i = 0;
        }
    }
    return deleted_gems;
}
*/
auto Blob::destroy_connectors(void) -> blob_t
{
    blob_t destroyed_connectors;

    auto connectors_to_destroy = std::remove_if(begin(blob), end(blob),
        [](const connector_t& connector){
            return connector.size() > 3;
    });

    std::move(connectors_to_destroy, end(blob), std::back_inserter(destroyed_connectors));

    blob.erase(connectors_to_destroy, end(blob));

    return destroyed_connectors;
}

auto Blob::total_connectors_to_destroy() -> count_t
{
    return std::count_if(cbegin(blob), cend(blob), [](const connector_t& connector){
        return connector.size() > 3;
    });
}

auto Blob::total_gems_to_destroy() -> count_t
{
    return std::transform_reduce(begin(blob), end(blob), 0, std::plus{},
        [](const connector_t& connector){
            return connector.size() > 3 ? connector.size() : 0;
    });
}

auto Blob::total_gems_to_destroy_of_color(const color_t color) -> count_t
{
    return std::transform_reduce(begin(blob), end(blob), 0, std::plus{},
        [color=color](const connector_t& connector){
            bool condition = connector.front()->get_color() == color && connector.size() > 3;
            return condition ? connector.size() : 0;
    });
}

auto Blob::get_blob_height() -> span_t
{
    return *std::max_element(begin(floor), end(floor));
}

auto Blob::update_floor() -> void
{
    for (const connector_t& connector: blob)
        for (auto it = connector.begin(); it != connector.end(); ++it)
            if (it->get()->get_y() < floor[it->get()->get_x()])
                floor[it->get()->get_x()] = it->get()->get_y();
}

/*
    int i = 0;
    std::for_each(begin(blob), end(blob), [](connector_t connector){
        if (connector.size() > 3)
            deleted_gems = std::move(connector);
            blob.erase()
    });
    {
        int connector_index = i;
        int connector_size = blob[connector_index].size();

        if ( connector_size > 3 )
        {
            deleted_gems = std::move( blob[ connector_index ] );
            blob.erase( blob.begin() + connector_index );
            i = 0;
        }
    }
    return deleted_gems;
}
*/

int Blob::get_red_gem_count()
{
    return 3;
}

int Blob::get_connector_count()
{
    return this->blob.size();
}

blob_t* Blob::get_blob()
{
    return &(this->blob);
}

bool Blob::gems_are_connected(gem_raw_ptr first, gem_raw_ptr second)
{

    bool gems_are_x_neighbors =
        abs( first->get_x() - second->get_x() ) == 1 && first->get_y() == second->get_y();
    bool gems_are_y_neighbors =
        abs( first->get_y() - second->get_y() ) == 1 && first->get_x() == second->get_x();

    return gems_are_x_neighbors || gems_are_y_neighbors;
}

count_t Blob::get_blob_size()
{
    return std::transform_reduce(begin(blob), end(blob), 0, std::plus{},
        [](const connector_t& connector){
            return connector.size();
    });
}



