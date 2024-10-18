#include "GemStack.h"
#include <tuple>

GemStack::GemStack(color_t first_color, color_t middle_color, color_t last_color): current_orientation(UP)
{
    first(gems) = std::make_unique<Gem>(first_color, settings::board_middle, settings::first_starting_y);
    middle(gems) = std::make_unique<Gem>(middle_color, settings::board_middle, settings::middle_starting_y);
    last(gems) = std::make_unique<Gem>(last_color, settings::board_middle, settings::last_starting_y);
}

GemStack::~GemStack()
{
}

int GemStack::gemstack_length()
{
    return std::tuple_size<decltype(this->gems)>::value;
}

gem_raw_ptr GemStack::get_first_gem()
{
    return first(gems).get();
}

gem_raw_ptr GemStack::get_middle_gem()
{
    return middle(gems).get();
}

gem_raw_ptr GemStack::get_last_gem()
{
    return last(gems).get();
}
/*
void GemStack::rotate_gemstack()
{
    this->gems = std::make_tuple(this->get_middle_gem(), this->get_last_gem(), this->get_first_gem());
}
*/
void GemStack::rotate_gemstack()
{
    std::rotate(gems.begin(), std::next(gems.begin()), gems.end());
}

orientation_t GemStack::get_current_orientation()
{
    return this->current_orientation;
}

void GemStack::toggle_orientation()
{
    switch (this->current_orientation)
    {
        case UP:
            this->current_orientation = RIGHT;
            break;
        case RIGHT:
            this->current_orientation = DOWN;
            break;
        case DOWN:
            this->current_orientation = LEFT;
            break;
        case LEFT:
            this->current_orientation = UP;
            break;
        default: break;
    }
}

xy_t GemStack::get_first_xy()
{
    return this->get_first_gem()->get_xy();
}

xy_t GemStack::get_middle_xy()
{
    return this->get_middle_gem()->get_xy();
}

xy_t GemStack::get_last_xy()
{
    return this->get_last_gem()->get_xy();
}

void GemStack::set_first_xy(int x, int y)
{
    this->get_first_gem()->set_xy(x,y);
}

void GemStack::set_middle_xy(int x, int y)
{
    this->get_middle_gem()->set_xy(x,y);
}

void GemStack::set_last_xy(int x, int y)
{
    this->get_last_gem()->set_xy(x,y);
}

int GemStack::get_first_x()
{
    return this->get_first_gem()->get_x();
}

int GemStack::get_first_y()
{
    return this->get_first_gem()->get_y();
}

int GemStack::get_middle_x()
{
    return this->get_middle_gem()->get_x();
}

int GemStack::get_middle_y()
{
    return this->get_middle_gem()->get_y();
}

int GemStack::get_last_x()
{
    return this->get_last_gem()->get_x();
}

int GemStack::get_last_y()
{
    return this->get_last_gem()->get_y();
}

void GemStack::advance_gemstack()
{
    switch (this->current_orientation)
    {
        case UP:
            this->set_first_xy(this->get_first_x(), this->get_first_y()+1);
            this->set_middle_xy(this->get_middle_x(), this->get_middle_y()+1);
            this->set_last_xy(this->get_last_x(), this->get_last_y()+1);
            break;
        default: break;
    }
}

void GemStack::shift_right()
{
    bool condition_1 = this->get_first_gem()->get_x() == settings::board_width;
    bool condition_2 = this->get_middle_gem()->get_x() == settings::board_width;
    bool condition_3 = this->get_last_gem()->get_x() == settings::board_width;

    if (condition_1 || condition_2 || condition_3) return;

    this->set_first_xy(this->get_first_x()+1, get_first_y());
    this->set_middle_xy(this->get_middle_x()+1, get_middle_y());
    this->set_last_xy(this->get_last_x()+1, this->get_last_y());
}

void GemStack::shift_left()
{
    bool condition_1 = this->get_first_gem()->get_x() == 0;
    bool condition_2 = this->get_middle_gem()->get_x() == 0;
    bool condition_3 = this->get_last_gem()->get_x() == 0;

    if (condition_1 || condition_2 || condition_3) return;

    this->set_first_xy(this->get_first_x()-1, get_first_y());
    this->set_middle_xy(this->get_middle_x()-1, get_middle_y());
    this->set_last_xy(this->get_last_x()-1, this->get_last_y());
}

void GemStack::set_orientation(const orientation_t new_orientation)
{
    if (new_orientation == this->current_orientation)
        return;

    Gem *middle_gem = this->get_middle_gem();

    bool current_orientation_is_up_or_down = (this->current_orientation == UP || this->current_orientation == DOWN);
    bool new_orientation_is_left_or_right = (new_orientation == LEFT || new_orientation == RIGHT);
    bool at_right_limit = this->get_first_gem()->get_x() == settings::board_width;
    bool at_left_limit = this->get_first_gem()->get_x() == 0;

    if (current_orientation_is_up_or_down && new_orientation_is_left_or_right && at_right_limit)
        switch (new_orientation) {
            case RIGHT:
                this->get_first_gem()->set_xy(middle_gem->get_x(), middle_gem->get_y());
                this->get_last_gem()->set_xy(middle_gem->get_x()-2, middle_gem->get_y());
                this->get_middle_gem()->set_xy(middle_gem->get_x()-1, middle_gem->get_y());
                break;
            case LEFT:
                this->get_last_gem()->set_xy(middle_gem->get_x(), middle_gem->get_y());
                this->get_first_gem()->set_xy(middle_gem->get_x()-2, middle_gem->get_y());
                this->get_middle_gem()->set_xy(middle_gem->get_x()-1, middle_gem->get_y());
                break;
            default: break;
        }
    else if (current_orientation_is_up_or_down && new_orientation_is_left_or_right && at_left_limit)
        switch (new_orientation) {
            case RIGHT:
                this->get_last_gem()->set_xy(middle_gem->get_x(), middle_gem->get_y());
                this->get_first_gem()->set_xy(middle_gem->get_x()+2, middle_gem->get_y());
                this->get_middle_gem()->set_xy(middle_gem->get_x()+1, middle_gem->get_y());
                break;
            case LEFT:
                this->get_first_gem()->set_xy(middle_gem->get_x(), middle_gem->get_y());
                this->get_last_gem()->set_xy(middle_gem->get_x()+2, middle_gem->get_y());
                this->get_middle_gem()->set_xy(middle_gem->get_x()+1, middle_gem->get_y());
                break;
            default: break;
        }
    else
        switch (new_orientation)
        {
            case UP:
                this->get_first_gem()->set_xy(middle_gem->get_x(), middle_gem->get_y()-1);
                this->get_last_gem()->set_xy(middle_gem->get_x(), middle_gem->get_y()+1);
                break;
            case RIGHT:
                this->get_first_gem()->set_xy(middle_gem->get_x()+1, middle_gem->get_y());
                this->get_last_gem()->set_xy(middle_gem->get_x()-1, middle_gem->get_y());
                break;
            case DOWN:
                this->get_first_gem()->set_xy(middle_gem->get_x(), middle_gem->get_y()+1);
                this->get_last_gem()->set_xy(middle_gem->get_x(), middle_gem->get_y()-1);
                break;
            case LEFT:
                this->get_first_gem()->set_xy(middle_gem->get_x()-1, middle_gem->get_y());
                this->get_last_gem()->set_xy(middle_gem->get_x()+1, middle_gem->get_y());
            default: break;
        }
    this->current_orientation = new_orientation;
}

void GemStack::sweep_right()
{
    switch (this->current_orientation) {
        case RIGHT:
            this->get_first_gem()->set_x(settings::board_width);
            this->get_middle_gem()->set_x(settings::board_width-1);
            this->get_last_gem()->set_x(settings::board_width-2);
            break;
        case LEFT:
            this->get_last_gem()->set_x(settings::board_width);
            this->get_middle_gem()->set_x(settings::board_width-1);
            this->get_first_gem()->set_x(settings::board_width-2);
            break;
        case UP:
        case DOWN:
            for (auto& gem: gems)
                gem->set_x(settings::board_width);
            break;
        default: break;
    }
}

void GemStack::sweep_left()
{
    switch (current_orientation) {
        case RIGHT:
            this->get_last_gem()->set_x(0);
            this->get_middle_gem()->set_x(1);
            this->get_first_gem()->set_x(2);
            break;
        case LEFT:
            this->get_first_gem()->set_x(0);
            this->get_middle_gem()->set_x(1);
            this->get_last_gem()->set_x(2);
            break;
        case DOWN:
        case UP:
            for (auto& gem: gems)
                gem->set_x(0);
            break;
        default: break;
    }

}

gemstack_t GemStack::get_gem_colors()
{
    color_t first_gem_color = this->get_first_gem()->get_color();
    color_t middle_gem_color = this->get_first_gem()->get_color();
    color_t last_gem_color = this->get_last_gem()->get_color();
    return std::make_tuple(first_gem_color, middle_gem_color, last_gem_color);
}
