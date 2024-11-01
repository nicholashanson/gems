#include "GemStack.h"
#include <tuple>

// special members
GemStack::GemStack() : current_orientation(UP) {}
GemStack::~GemStack(){}

auto GemStack::get_first_x() -> x_t{return get_first_gem()->get_x();}
auto GemStack::get_first_y() -> y_t{return get_first_gem()->get_y();}
auto GemStack::get_middle_x() -> x_t{return get_middle_gem()->get_x();}
auto GemStack::get_middle_y() -> y_t{return get_middle_gem()->get_y();}
auto GemStack::get_last_x() -> x_t{return get_last_gem()->get_x();}
auto GemStack::get_last_y() -> y_t{return get_last_gem()->get_y();}
auto GemStack::get_first_xy() -> xy_t{return get_first_gem()->get_xy();}
auto GemStack::get_middle_xy() -> xy_t{return get_middle_gem()->get_xy();}
auto GemStack::get_last_xy() -> xy_t{return get_last_gem()->get_xy();}

auto GemStack::gemstack_length() const -> int{return gems.size();}

auto GemStack::get_current_orientation() const -> orientation_t{return current_orientation;}

auto GemStack::get_first_gem() -> gem_raw_ptr{return first(gems).get();}
auto GemStack::get_middle_gem() -> gem_raw_ptr{return middle(gems).get();}
auto GemStack::get_last_gem() -> gem_raw_ptr{return last(gems).get();}

// setters
auto GemStack::set_first_xy(const x_t x, const y_t y) -> void{this->get_first_gem()->set_xy(x,y);}
auto GemStack::set_middle_xy(const x_t x, const y_t y) -> void{this->get_middle_gem()->set_xy(x,y);}
auto GemStack::set_last_xy(const x_t x, const y_t y) -> void{this->get_last_gem()->set_xy(x,y);}

auto GemStack::get_gems() -> gemstack_elements_t*{return &gems;}

auto GemStack::get_gem_colors() -> gemstack_colors_t
{
    return gemstack_colors_t{
        get_first_gem()->get_color(),
        get_middle_gem()->get_color(),
        get_last_gem()->get_color() };
}

auto GemStack::rotate_gemstack() -> void
{
    swap_colors( first(gems).get(), last(gems).get() );
    swap_colors( last(gems).get(), middle(gems).get() );
}

auto GemStack::toggle_orientation() -> void
{
    switch ( current_orientation )
    {
        case UP:
            current_orientation = RIGHT;
            break;
        case RIGHT:
            current_orientation = DOWN;
            break;
        case DOWN:
            current_orientation = LEFT;
            break;
        case LEFT:
            current_orientation = UP;
            break;
        default: break;
    }
}

auto GemStack::advance_gemstack() -> void
{
   for (auto& gem: gems)
        gem->inc_y();
}

auto GemStack::shift_right() -> void
{
    // check not at the edge already
    for (auto& gem: gems)
        if ( gem->get_x() == settings::board_width )
            return;

    // move one space to the right
    for (auto& gem: gems)
        gem->set_x( gem->get_x() + 1 );
}

auto GemStack::shift_left() -> void
{
    // check not already at the edge
    for (auto& gem: gems)
        if ( gem->get_x() == 0 )
            return;

    // move one space to the left
    for (auto& gem: gems)
        gem->set_x( gem->get_x() - 1 );
}

auto GemStack::set_orientation(const orientation_t new_orientation) -> void
{
    if ( new_orientation == current_orientation )
        return;

    const y_t m_y = get_middle_gem()->get_y();
    const x_t m_x = get_middle_gem()->get_x();

    const bool current_orientation_is_up_or_down =
        ( current_orientation == UP || current_orientation == DOWN );
    const bool new_orientation_is_left_or_right =
        ( new_orientation == LEFT || new_orientation == RIGHT );

    const bool at_right_limit =
        LEFT == current_orientation ?
            get_last_gem()->get_x() == settings::board_width
            : get_first_gem()->get_x() == settings::board_width;
    const bool at_left_limit =
        RIGHT == current_orientation ?
            get_last_gem()->get_x() == 0
            : get_first_gem()->get_x() == 0;

    if ( current_orientation_is_up_or_down
         && new_orientation_is_left_or_right
         && at_right_limit)
        if ( RIGHT == new_orientation ) {
                get_first_gem()->set_xy(m_x, m_y);
                get_last_gem()->set_xy(m_x-2, m_y);
                get_middle_gem()->set_xy(m_x-1, m_y);
        } else {
                get_last_gem()->set_xy(m_x, m_y);
                get_first_gem()->set_xy(m_x-2, m_y);
                get_middle_gem()->set_xy(m_x-1, m_y);
        }

    else if (
        current_orientation_is_up_or_down
        && new_orientation_is_left_or_right
        && at_left_limit )
        if ( RIGHT == new_orientation ) {
            get_last_gem()->set_xy(m_x, m_y);
            get_first_gem()->set_xy(m_x+2, m_y);
            get_middle_gem()->set_xy(m_x+1, m_y);
        } else {
            get_first_gem()->set_xy(m_x, m_y);
            get_last_gem()->set_xy(m_x+2, m_y);
            get_middle_gem()->set_xy(m_x+1, m_y);
        }

    else
        switch (new_orientation)
        {
            case UP:
                get_first_gem()->set_xy(m_x, m_y-1);
                get_last_gem()->set_xy(m_x, m_y+1);
                break;
            case RIGHT:
                get_first_gem()->set_xy(m_x+1, m_y);
                get_last_gem()->set_xy(m_x-1, m_y);
                break;
            case DOWN:
                get_first_gem()->set_xy(m_x, m_y+1);
                get_last_gem()->set_xy(m_x, m_y-1);
                break;
            case LEFT:
                get_first_gem()->set_xy(m_x-1, m_y);
                get_last_gem()->set_xy(m_x+1, m_y);
            default: break;
        }

    current_orientation = new_orientation;
}

auto GemStack::sweep_right(const span_t distance) -> void
{
    for (gem_uptr& gem: gems)
        gem->jump_x(distance);
}

auto GemStack::sweep_left(const span_t distance) -> void
{
    for (gem_uptr& gem: gems)
        gem->jump_x(-distance);
}

auto GemStack::populate_gemstack(gemstack_colors_t gem_colors) -> void
{
    first(gems) = std::make_unique<Gem>(
        first(gem_colors),
        settings::board_middle,
        settings::first_starting_y);
    middle(gems) = std::make_unique<Gem>(
        middle(gem_colors),
        settings::board_middle,
        settings::middle_starting_y);
    last(gems) = std::make_unique<Gem>(
        last(gem_colors),
        settings::board_middle,
        settings::last_starting_y);
}




