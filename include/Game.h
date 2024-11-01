#ifndef GAME_H
#define GAME_H
#include "definitions.h"
#include "GemStack.h"
#include "Blob.h"
#include "macros.h"

class Game
{
    public:
        Game();
        virtual ~Game();

        // getters
        auto get_first_xy() -> xy_t;
        auto get_first_x() -> x_t;
        auto get_first_y() -> y_t;
        auto get_middle_x() -> x_t;
        auto get_middle_y() -> y_t;
        auto get_last_x() -> x_t;
        auto get_last_y() -> y_t;
        auto get_current_gemstack() -> gemstack_raw_ptr;
        auto get_gemstack_orientation() const -> orientation_t;
        auto get_next_gemstack_colors() const -> gemstack_colors_t;
        auto get_blob() -> blob_t*;
        auto get_grid() -> grid_t*;
        auto get_current_gemstack_colors() -> gemstack_colors_t;
        auto get_floor() const -> floor_t;
        auto get_status() const -> status_t;
        auto get_current_score() const -> score_t;

        // setters
        auto set_status(const status_t) -> void;
        auto set_gemstack_orientation(const orientation_t) -> void;

        // checkers
        auto grid_is_cascading() const -> bool;
        auto game_is_over() const -> bool;
        auto game_is_paused() const -> bool;
        auto gemstack_is_at_floor() -> bool;

        // stats
        auto count_gems_in_blob() const -> count_t;
        auto measure_longest_connector() const -> span_t;
        auto count_gems_in_grid() const -> count_t;
        auto count_columns_in_grid() const -> count_t;
        auto count_connectors_in_blob() const -> count_t;
        auto count_gems_of_color(color_t) const -> count_t;
        auto count_connectors_to_destroy() const -> count_t;
        auto count_gems_to_destroy() const -> count_t;

        // actions
        auto add_points(const blob_t&) -> void;
        auto advance_game() -> void;
        auto add_gem_layer() -> void;
        auto reset_blob() -> void;
        auto convert_blob_to_grid() -> void;
        auto cascade_grid() -> bool;
        auto generate_test_blob() -> void;
        auto toggle_gemstack_orientation() -> void;
        auto advance_gemstack() -> void;
        auto sweep_gemstack_right() -> void;
        auto sweep_gemstack_left() -> void;
        auto shift_gemstack_right() -> void;
        auto shift_gemstack_left() -> void;
        auto rotate_gemstack() -> void;
        auto update_gemstack() -> void;
        auto add_gem_to_blob(gem_uptr) -> void;
        auto add_current_gemstack_to_blob() -> void;
        auto add_gemstack_to_blob(gemstack_elements_t) -> void;
        auto destroy_blob_connectors() -> blob_t;
        auto update_floor() -> void;
    private:
        // checkers
        auto __current_gemstack_is_shift_left_blocked() -> bool;
        auto __current_gemstack_is_shift_right_blocked() -> bool;
        auto __current_gemstack_is_rotation_blocked() -> bool;

        // stats
        auto __measure_distance_to_right_blocking_gem() -> span_t;
        auto __measure_distance_to_left_blocking_gem() -> span_t;
        auto __measure_distance_to_left_blocking_gem_from(const x_t, const y_t) const -> span_t;
        auto __measure_distance_to_right_blocking_gem_from(const x_t, const y_t) const -> span_t;

        // actions
        auto __generate_gemstack() -> void;
        auto __generate_next_gemstack_colors() -> void;
    public:
        // utilities
        auto get_random_gem_color() -> color_t;
    protected:

    private:
        GemStack current_gemstack;
        gemstack_colors_t next_gemstack_colors;
        Blob blob;
        std::random_device rd;
        std::default_random_engine generator;
        std::uniform_int_distribution<int> distribution;
        grid_t grid;
        status_t current_status;
        score_t current_score;
};

#endif // GAME_H
