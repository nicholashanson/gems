#include "Gem.h"

// special members
Gem::Gem(){}
Gem::Gem(color_t color, int x, int y) :
    gem_color(color),
    position(std::make_pair(x,y)){}
Gem::~Gem(){}

// getters
auto Gem::get_x() const -> x_t
{return left(position);}

auto Gem::get_y() const -> y_t
{return right(position);}

auto Gem::get_xy() const -> xy_t
{return position;}

auto Gem::get_color() const -> color_t
{return gem_color;}

// setters
auto Gem::set_x(x_t x) -> void
{left(position) = x;}

auto Gem::set_y(y_t y) -> void
{right(position) = y;}

auto Gem::set_xy(x_t x, y_t y) -> void
{position = std::make_pair( x, y );}

// actions
auto Gem::inc_y() -> void
{++right(position);}

auto Gem::jump_x(span_t distance) -> void
{left(position) += distance;}

// friend
auto swap_colors(gem_raw_ptr lhs, gem_raw_ptr rhs) -> void
{
    color_t temp = lhs->gem_color;
    lhs->gem_color = rhs->gem_color;
    rhs->gem_color = temp;
}
