#include "Gem.h"

Gem::Gem()
{
}

Gem::Gem(color_t color, int x, int y) : gem_color(color), position(std::make_pair(x,y))
{
}

Gem::~Gem()
{
    //dtor
}

color_t Gem::get_color() const
{
    return this->gem_color;
}

xy_t Gem::get_xy() const
{
    return this->position;
}

int Gem::get_x() const
{
    return left(this->position);
}

int Gem::get_y() const
{
    return right(this->position);
}

void Gem::set_xy(int x, int y)
{
    this->position = std::make_pair(x, y);
}

void Gem::set_x(int x)
{
    left(this->position) = x;
}

void Gem::set_y(int y)
{
    right(this->position) = y;
}



