#ifndef DEFINITIONS_H
#define DEFINITIONS_H
//#define TEST
#include <array>
#include "settings.h"
#include <memory>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <numeric>
#include <list>
#include <random>
#include <ranges>
#include <iterator>
#include <cassert>
#include <map>
#include <functional>

class Gem;
class GemStack;

typedef enum {
    RED_C = 0,
    BLUE_C,
    GREEN_C,
    YELLOW_C,
    ORANGE_C
} color_t;

typedef enum {
    UP,
    RIGHT,
    DOWN,
    LEFT
} orientation_t;

typedef enum
{
    PAUSED,
    ACTIVE
} status_t;

// scalar types
typedef int x_t;
typedef int y_t;
typedef int span_t;
typedef int count_t;
typedef int score_t;
typedef bool check_t;

// iterators
typedef Gem* gem_raw_ptr;
typedef GemStack* gemstack_raw_ptr;
typedef std::unique_ptr<Gem> gem_uptr;
typedef std::vector<int>::iterator top_gem_it;

// aggregate types
typedef std::pair<int,int> xy_t;
typedef std::list<gem_uptr> connector_t;
typedef std::vector<connector_t> blob_t;
typedef std::vector<gem_raw_ptr> column_t;
typedef std::array<color_t, 3> gemstack_colors_t;
typedef std::array<gem_uptr, 3> gemstack_elements_t;
typedef std::array<int,settings::board_width+1> floor_t;
typedef std::array<column_t, settings::board_width + 1> grid_t;

#endif // DEFINITIONS_H
