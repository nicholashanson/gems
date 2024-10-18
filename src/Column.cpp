#include "Column.h"
#include "definitions.h"

Column::Column()
{
    this->gems.resize(settings::board_height);
    this->top_gem = gems.end();
}

Column::~Column()
{
    //dtor
}

bool Column::is_full()
{
    return this->top_gem == gems.begin();
}

bool Column::is_empty()
{
    return this->top_gem == gems.end();
}

void Column::add_gem(const Gem& gem)
{
    --top_gem;
    *top_gem = gem.get_y();
}
