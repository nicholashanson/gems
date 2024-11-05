#ifndef GEMSTACK_H
#define GEMSTACK_H
#include "definitions.h"
#include "Gem.h"
#include "macros.h"

class GemStack
{
    public:
        GemStack();
        virtual ~GemStack();

        // getters
        auto get_first_gem() -> gem_raw_ptr;
        auto get_middle_gem() -> gem_raw_ptr;
        auto get_last_gem() -> gem_raw_ptr;
        auto get_first_xy() -> xy_t;
        auto get_middle_xy() -> xy_t;
        auto get_last_xy() -> xy_t;
        auto get_first_x() -> x_t;
        auto get_first_y() -> y_t;
        auto get_middle_x() -> x_t;
        auto get_middle_y() -> y_t;
        auto get_last_x() -> x_t;
        auto get_last_y() -> y_t;
        auto gemstack_length() const -> int;
        auto get_gems() -> gemstack_elements_t*;
        auto get_gem_colors() -> gemstack_colors_t;
        auto get_current_orientation() const -> orientation_t;

        // setters
        auto set_first_xy(int x, int y) -> void;
        auto set_middle_xy(int x, int y) -> void;
        auto set_last_xy(int x, int y) -> void;

        // actions
        auto rotate_gemstack() -> void;
        auto advance_gemstack() -> void;
        auto toggle_orientation() -> void;
        auto populate_gemstack(const gemstack_colors_t) -> void;

        auto shift_right() -> void;
        auto shift_left() -> void;
        auto set_orientation(const orientation_t) -> void;
        auto sweep_right(span_t) -> void;
        auto sweep_left(span_t) -> void;

        auto print_gemstack() -> void;
    protected:

    private:
        gemstack_elements_t gems;
        orientation_t current_orientation;
};

#endif // GEMSTACK_H
