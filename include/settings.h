namespace settings {
    const int board_width = 9;
    const int board_height = 14;
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
    const int square_size = 30;
    constexpr int gem_radius = square_size / 2;

    // board
    constexpr int board_height_in_pixels = square_size*(board_height+1);
    constexpr int board_width_in_pixels = square_size*(board_width+1);
    constexpr int board_x_offset = square_size;
    constexpr int board_y_offset = square_size;

    // text
    constexpr int text_x_offset = square_size / 2;
    constexpr int text_y_offset = square_size / 4;

    // points count
    constexpr int points_count_x_offset = board_x_offset +
        board_width_in_pixels + square_size;
    constexpr int points_count_y_offset = board_y_offset +
        board_height_in_pixels / 2;
    constexpr int points_count_width = 5 * square_size;

    // window
    constexpr int window_width = board_x_offset + (board_width+1)*square_size + square_size*10;
    constexpr int window_height = board_y_offset + (board_height+1)*square_size + square_size;
}


