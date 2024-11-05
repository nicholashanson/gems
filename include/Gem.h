#ifndef GEM_H
#define GEM_H
#include "definitions.h"
#include "macros.h"

class Gem
{
    public:
        Gem();
        Gem(color_t,int,int);
        virtual ~Gem();

        // getters
        auto get_color() const -> color_t;
        auto get_xy() const -> xy_t;
        auto get_x() const -> int;
        auto get_y() const -> int;

        // setters
        auto set_x(x_t) -> void;
        auto set_y(y_t) -> void;
        auto set_xy(x_t,y_t) -> void;

        // actions
        auto inc_y() -> void;
        auto jump_x(span_t) -> void;

        friend auto swap_colors(const gem_raw_ptr,const gem_raw_ptr) -> void;
    protected:

    private:
        xy_t position;
        color_t gem_color;
};
#endif // GEM_H
