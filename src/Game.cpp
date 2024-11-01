#include "Game.h"

// special members
Game::Game():
    generator( rd() ),
    distribution( 0, settings::number_of_gem_colors - 1 ),
    current_status(ACTIVE),
    current_score( 0 )
{
    __generate_next_gemstack_colors();
    current_gemstack.populate_gemstack(next_gemstack_colors);
    __generate_next_gemstack_colors();
}
Game::~Game(){}

// getters
auto Game::get_current_score() const -> score_t{return current_score;}

auto Game::get_first_x() -> x_t{return current_gemstack.get_first_x();}
auto Game::get_first_y() -> y_t{return current_gemstack.get_first_y();}
auto Game::get_first_xy() -> xy_t{return current_gemstack.get_first_xy();}
auto Game::get_middle_x() -> x_t{return current_gemstack.get_middle_x();}
auto Game::get_middle_y() -> y_t{return current_gemstack.get_middle_y();}
auto Game::get_last_x() -> x_t{return current_gemstack.get_last_x();}
auto Game::get_last_y() -> y_t{return current_gemstack.get_last_y();}
auto Game::get_current_gemstack() -> GemStack* {return &current_gemstack;}
auto Game::get_gemstack_orientation() const -> orientation_t{return current_gemstack.get_current_orientation();}
auto Game::get_current_gemstack_colors() -> gemstack_colors_t{return current_gemstack.get_gem_colors();}
auto Game::get_next_gemstack_colors() const -> gemstack_colors_t{return next_gemstack_colors;}

auto Game::get_floor() const -> floor_t{return blob.get_floor();}

auto Game::get_grid() -> grid_t*{return &grid;}

// setters
auto Game::set_gemstack_orientation(const orientation_t ori) -> void {current_gemstack.set_orientation(ori);}

// checkers
auto Game::__current_gemstack_is_rotation_blocked() -> bool
{
    // if the gemstack has LEFT or RIGHT orientation it can
    // rotate freely
    if ( RIGHT == current_gemstack.get_current_orientation()
         || LEFT == current_gemstack.get_current_orientation() )
        return false;

    // check if gemstack is at left board-edge
    if ( 0 == current_gemstack.get_middle_x() )
        // check right-hand-side gem is not blocking
        if ( get_floor()[1] >= current_gemstack.get_middle_y() )
            // not blocking
            return false;
        // blocking
        else return true;

    // check if gemstack is at right board-edge
    else if ( settings::board_width == current_gemstack.get_middle_x() )
        // check left-hand-side gem is not blocking
        if ( get_floor()[ settings::board_width - 1]
             >= current_gemstack.get_middle_y() )
            // not blocking
            return false;
        // blocking
        else return true;

    // gemstack is neither of the above edge cases
    // so check left and right side for blocking
    // check left-side
    else if ( get_floor()[ current_gemstack.get_middle_x() - 1 ] >= current_gemstack.get_middle_y()
         // or right_side neighboring gem
         && get_floor()[ current_gemstack.get_middle_x() + 1 ] >= current_gemstack.get_middle_y() )
        // gemstack is not blocked
        return false;
    // gemstack is blocked
    else
        return true;
}

auto Game::__current_gemstack_is_shift_left_blocked() -> bool
{
    if ( LEFT == current_gemstack.get_current_orientation()
         || UP == current_gemstack.get_current_orientation() )
        if ( get_floor()[ current_gemstack.get_first_x() - 1 ]
             >= current_gemstack.get_first_y() )
            return false;
        else return true;
    else
        if ( get_floor()[ current_gemstack.get_last_x() - 1 ]
             >= current_gemstack.get_last_y() )
            return false;
        else return true;
}

auto Game::__current_gemstack_is_shift_right_blocked() -> bool
{
    if ( RIGHT == current_gemstack.get_current_orientation()
         || UP == current_gemstack.get_current_orientation() )
        if ( get_floor()[ current_gemstack.get_first_x() + 1 ]
             >= current_gemstack.get_first_y() )
            return false;
        else return true;
    else
        if ( get_floor()[ current_gemstack.get_last_x() + 1 ]
             >= current_gemstack.get_last_y() )
            return false;
        else return true;
}

auto Game::__measure_distance_to_right_blocking_gem_from(const x_t x_, const y_t y_ ) const -> span_t
{
    const floor_t floor = get_floor();
    
    auto x = floor.cbegin();
    
    std::advance( x, x_ );
    
    auto it = std::find_if( std::next( x ), floor.cend(),
        [&](const int& y){
            return y < y_;
    });
    
    return std::distance( x, it ) - 1;
}

auto Game::__measure_distance_to_left_blocking_gem_from(const x_t x_, const y_t y_) const -> span_t
{
    const floor_t floor = get_floor();
    
    auto x = floor.crbegin();
    
    std::advance( x, floor.size() - x_ );
    
    auto it = std::find_if( x, floor.crend(),
        [&](const int& y){
            return y < y_;
    });
    
    return std::distance( std::prev(x), it ) - 1;
}

auto Game::__measure_distance_to_right_blocking_gem() -> span_t
{
    if ( current_gemstack.get_current_orientation() == RIGHT
         || current_gemstack.get_current_orientation() == UP )
        return __measure_distance_to_right_blocking_gem_from(
            current_gemstack.get_first_x(), current_gemstack.get_first_y() );
    else
        return __measure_distance_to_right_blocking_gem_from(
            current_gemstack.get_last_x(), current_gemstack.get_last_y() );
}

auto Game::__measure_distance_to_left_blocking_gem() -> span_t
{
    if ( current_gemstack.get_current_orientation() == LEFT
         || current_gemstack.get_current_orientation() == UP )
        return __measure_distance_to_left_blocking_gem_from(
            current_gemstack.get_first_x(), current_gemstack.get_first_y() );
    else
        return __measure_distance_to_left_blocking_gem_from(
            current_gemstack.get_last_x(), current_gemstack.get_last_y() );
}

auto Game::generate_test_blob() -> void
{
    for (int i = 0; i <= settings::board_width; i++)
        for (int j = 0; j <= settings::board_height; j++)
            blob.add_gem_to_blob( std::make_unique<Gem>
                                  ( get_random_gem_color(),
                                    i, j ));
}

auto Game::add_gem_layer() -> void
{
    for ( int i = 0; i <= settings::board_width; i++ )
        add_gem_to_blob( std::make_unique<Gem>(
                         get_random_gem_color(),
                         i, get_floor()[i]) );
}

auto Game::count_connectors_in_blob() const -> count_t{return blob.count_connectors();}

auto Game::get_blob() -> blob_t*{return blob.get_blob();}

auto Game::add_gem_to_blob(gem_uptr gem) -> void{return blob.add_gem_to_blob( std::move(gem) );}

auto Game::destroy_blob_connectors() -> blob_t{return blob.destroy_connectors();}

auto Game::count_gems_in_blob() const -> count_t{return blob.count_gems_in_blob();}

auto Game::add_current_gemstack_to_blob() -> void
{
    // special case: if the gemstack is orientated downward then
    // we need to add it's gems to the blob in reverse
    if ( DOWN == current_gemstack.get_current_orientation() )
        for ( gem_uptr& gem: *current_gemstack.get_gems() | std::views::reverse )
             blob.add_gem_to_blob( std::move( gem ) );
    else
        for ( gem_uptr& gem: *current_gemstack.get_gems() )
             blob.add_gem_to_blob( std::move( gem ) );
}

auto Game::get_random_gem_color() -> color_t{return static_cast<color_t>( distribution ( generator ) );}

auto Game::__generate_next_gemstack_colors() -> void
{
    for ( color_t& color: next_gemstack_colors )
        color = get_random_gem_color();
}

auto Game::update_gemstack() -> void
{
    current_gemstack.populate_gemstack( next_gemstack_colors );
    __generate_next_gemstack_colors();
}

auto Game::count_columns_in_grid() const -> count_t
{
    return std::count_if(grid.begin(), grid.end(),
        []( auto& column ){
        return !column.empty();
    });
}

auto Game::convert_blob_to_grid() -> void
{
    std::for_each(grid.begin(), grid.end(),
        []( column_t& column ){
            column.clear();
    });
    
    for ( connector_t& connector: *blob.get_blob() )
        for ( gem_uptr& gem: connector )
            grid[ gem->get_x() ].push_back( gem.get() );
            
    for ( column_t& column: grid )
        std::sort(column.begin(), column.end(),
            []( const gem_raw_ptr lhs, const gem_raw_ptr rhs ){
                return lhs->get_y() > rhs->get_y();
        });
}

auto Game::cascade_grid() -> bool
{
    bool cascaded = false;
    for ( column_t& column: grid )
        for ( int i = settings::board_height; i >= 0; --i ){
            if ( ( settings::board_height + 1 ) - i > column.size() ){
                break;
            }
            if ( column[ settings::board_height - i ]->get_y() < i ){
                column[ settings::board_height - i ]->inc_y();
                cascaded = true;
            }
        }
    return cascaded;
}

// stats
auto Game::count_connectors_to_destroy() const -> count_t{return blob.count_connectors_to_destroy();}
auto Game::count_gems_to_destroy() const -> count_t{return blob.count_gems_to_destroy();}
auto Game::count_gems_of_color(const color_t color) const -> count_t{return blob.count_gems_of_color(color);}
auto Game::measure_longest_connector() const -> span_t{return blob.measure_longest_connector();}

auto Game::count_gems_in_grid() const -> count_t
{
    return std::transform_reduce(grid.begin(), grid.end(), 0, std::plus{},
        []( const column_t& column ){
            return column.size();
    });
}

// checkers
auto Game::game_is_over() const -> bool
{
    const floor_t floor = get_floor();
    return std::any_of(floor.cbegin(),
                        floor.cend(),
                        []( const y_t& y ){
        return y <= -2;
    });
}

auto Game::grid_is_cascading() const -> bool
{
    for ( const column_t& column: grid )
        for ( int i = 0; i < column.size(); i++ )
            if ( column[ i ]->get_y() < settings::board_height - i )
                return true;
    return false;
}

auto Game::game_is_paused() const -> bool{return PAUSED == current_status;}

auto Game::gemstack_is_at_floor() -> bool
{
    gemstack_elements_t* gemstack_gems = current_gemstack.get_gems();
    return std::any_of(
        ( *gemstack_gems ).cbegin(),
        ( *gemstack_gems ).cend(),
        [&]( const gem_uptr& gem ){
            return gem->get_y() == blob.get_floor()[ gem->get_x() ];
    });
}

// setters
auto Game::set_status(status_t new_status) -> void{current_status = new_status;}

// actions
auto Game::advance_gemstack() -> void{current_gemstack.advance_gemstack();}
auto Game::rotate_gemstack() -> void{current_gemstack.rotate_gemstack();}

auto Game::shift_gemstack_left() -> void
{
    if ( !__current_gemstack_is_shift_left_blocked() )
        current_gemstack.shift_left();
    else return;
}

auto Game::shift_gemstack_right() -> void
{
    if ( !__current_gemstack_is_shift_right_blocked() )
        current_gemstack.shift_right();
    else return;
}

auto Game::sweep_gemstack_left() -> void
{
    current_gemstack.sweep_left(
        __measure_distance_to_left_blocking_gem()
    );
}

auto Game::sweep_gemstack_right() -> void
{
    current_gemstack.sweep_right(
        __measure_distance_to_right_blocking_gem()
    );
}

auto Game::toggle_gemstack_orientation() -> void
{
    // this function rotates the gemstack in space around
    // its center
    // before we rotate the gemstack we need to check if it
    // isn't blocked by gems on its left or right side
    // this can happen if the gemstack is orientated either
    // UP or DOWN before rotation
    if ( ( UP == current_gemstack.get_current_orientation()
          || DOWN == current_gemstack.get_current_orientation() )
          && __current_gemstack_is_rotation_blocked() )
        // the gemstack is blocked by neighboring gems either to
        // the left or right or both, so just rotate the gemstack
        // in the vertical direction
        // UP => DOWN ...
        if ( UP == current_gemstack.get_current_orientation() )
            current_gemstack.set_orientation( DOWN );
        // or DOWN => UP
        else current_gemstack.set_orientation( UP );
    // gemstack is free to rotate in any direction
    // so just toggle orientation normally
    else current_gemstack.toggle_orientation();
}


auto Game::update_floor() -> void{blob.update_floor();}

auto Game::reset_blob() -> void
{
    std::vector<gem_uptr> temp;
    
    temp.reserve( blob.count_gems_in_blob() );

    for ( connector_t& connector: *get_blob() )
        for ( gem_uptr& gem: connector )
            temp.push_back( std::move( gem ) );

    blob.clear_blob();

    for ( gem_uptr& gem: temp )
        blob.add_gem_to_blob( std::move( gem ) );
}

auto Game::add_points(const blob_t& destroyed_connectors) -> void
{
    current_score += std::transform_reduce( destroyed_connectors.begin(),
        destroyed_connectors.end(), 0, std::plus{},
                  [](const connector_t& connector){
        return settings::points_per_gemstack +
            ( settings::points_per_additional_gem *
            ( connector.size() - settings::gems_to_connect ) );
    });
}

auto Game::advance_game() -> void
{
    if ( game_is_paused() )
        return;
    convert_blob_to_grid();
    update_floor();
    if ( grid_is_cascading() ){
        cascade_grid();
        return;
    }
    reset_blob();
    if ( gemstack_is_at_floor() ){
        add_current_gemstack_to_blob();
        update_gemstack();
        return;
    }
    add_points( destroy_blob_connectors() );
    advance_gemstack();
}








