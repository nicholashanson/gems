#ifndef SETTINGS_H
#define SETTINGS_H

namespace settings {
    const int board_width = 5;
    const int board_height = 12;
    constexpr int board_size = (board_height+1)*(board_width+1);

    // gemstack
    constexpr int board_middle =  board_width / 2;
    constexpr int first_starting_y = -1;
    constexpr int middle_starting_y = first_starting_y - 1;
    constexpr int last_starting_y = middle_starting_y - 1;

    // game
    const int points_per_gemstack = 3;
    const int points_per_additional_gem = 2;
    const int number_of_gem_colors = 5;
    const int number_to_connect = 4;
    const int gems_in_gemstack = 3;
    const int gems_to_connect = 3;

    // gems
    const int square_size = 40;
    constexpr int gem_radius = square_size / 2;

    // board
    constexpr int board_height_in_pixels = square_size*(board_height+1);
    constexpr int board_width_in_pixels = square_size*(board_width+1);
    constexpr int board_x_offset = square_size*7;
    constexpr int board_y_offset = square_size / 2;

    // text
    constexpr int text_x_offset = square_size / 2;
    constexpr int text_y_offset = square_size / 4;

    // points count
    constexpr int points_count_x_offset = board_x_offset +
        board_width_in_pixels + square_size;
    constexpr int points_count_y_offset = board_y_offset +
        board_height_in_pixels / 2;
    constexpr int points_count_width = 4 * square_size;

    // window
    constexpr int window_width = settings::square_size*20;
    constexpr int window_height = settings::square_size*14;

    // next gems
    constexpr int next_gems_container_x_offset = board_x_offset + board_width_in_pixels + square_size / 2;
    constexpr int next_gems_x_offset = settings::next_gems_container_x_offset;
    constexpr int next_gems_y_offset = board_y_offset;
    constexpr int next_gems_width = square_size;
    constexpr int next_gems_height = square_size*3;
}

#endif // SETTINGS_H
