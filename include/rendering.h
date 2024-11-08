#include "raylib.h"
#include "definitions.h"
#include "settings.h"
#include "Gem.h"
#include "GemStack.h"

static blob_t destroyed_gems;
static int flash_gems_count = 0;

auto flash_gems() -> void;

// drawing
auto draw_board() -> void;
auto draw_background() -> void;
auto draw_blob(const blob_t*) -> void;
auto draw_points_count(const score_t) -> void;
auto draw_gemstack(GemStack*) -> void;
auto draw_gem(const gemstack_raw_ptr) -> void;
auto draw_next_gems(const gemstack_colors_t) -> void;

// utilities
auto get_gem_x_coord(const int) -> int;
auto get_gem_y_coord(const int) -> int;


