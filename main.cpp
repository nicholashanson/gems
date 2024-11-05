#ifndef TEST
#include "Game.h"
#include "raylib.h"

auto get_gem_x_coord(int) -> int;
auto get_gem_y_coord(int) -> int;
int flash_gems_count = 0;
blob_t destroyed_gems;

void draw_gem(const gem_raw_ptr gem)
{
    Rectangle rec = {
                get_gem_x_coord(gem->get_x()),
                get_gem_y_coord(gem->get_y()),
                settings::square_size,
                settings::square_size
            };
    switch (gem->get_color()){
        case YELLOW_C:
            DrawPoly(
                      Vector2{
                          get_gem_x_coord(gem->get_x()) + settings::square_size / 2,
                          get_gem_y_coord(gem->get_y()) + settings::square_size / 2},
                      6,
                      settings::square_size / 2,
                      90,
                      YELLOW);
            break;
        case BLUE_C:
            DrawRectangleRounded(
                      rec,
                      0.2f,
                      0,
                      BLUE);
            break;
        case GREEN_C:
            DrawPoly(
                      Vector2{
                          get_gem_x_coord(gem->get_x()) + settings::square_size / 2,
                          get_gem_y_coord(gem->get_y()) + settings::square_size / 2},
                      8,
                      settings::square_size / 2,
                      360/16,
                      GREEN);
            break;
        case ORANGE_C:
            DrawPoly(
                      Vector2{
                          get_gem_x_coord(gem->get_x()) + settings::square_size / 2,
                          get_gem_y_coord(gem->get_y()) + settings::square_size / 2},
                      6,
                      settings::square_size / 2,
                      0,
                      ORANGE);
            break;
        case RED_C:
            DrawCircle(
                      get_gem_x_coord(gem->get_x()) + settings::square_size / 2,
                      get_gem_y_coord(gem->get_y()) + settings::square_size / 2,
                      settings::gem_radius,
                      RED );
            break;
        default: break;
    }
}

void draw_blob(const blob_t* blob)
{
    for (auto& connector: *blob)
        if (connector.size() >= settings::gems_to_connect)
            for (auto& gem: connector)
                DrawRectangle(
                      get_gem_x_coord(gem->get_x()),
                      get_gem_y_coord(gem->get_y()),
                      settings::square_size,
                      settings::square_size,
                      WHITE );
        else
            for (auto& gem: connector)
                draw_gem(gem.get());
}

auto draw_points_count(score_t current_score) -> void
{
   DrawRectangle( settings::points_count_x_offset,
                  settings::points_count_y_offset,
                  settings::points_count_width,
                  settings::square_size,
                  BLACK );
   DrawText(TextFormat( "Score: %03i",
                        current_score ),
                        settings::points_count_x_offset + settings::text_x_offset,
                        settings::points_count_y_offset + settings::text_y_offset,
                        20,
                        WHITE );
}

auto get_gem_x_coord(int i) -> int
{
    return i*settings::square_size + settings::board_x_offset;
}

auto get_gem_y_coord(int j) -> int
{
    return j*settings::square_size + settings::board_y_offset;
}

auto draw_gemstack(GemStack* gemstack)
{
    for ( const auto& gem: *( gemstack->get_gems() ) )
        draw_gem( gem.get() );
}

auto draw_board() -> void
{
    DrawRectangle( settings::board_x_offset,
                   settings::board_y_offset,
                   settings::board_width_in_pixels,
                   settings::board_height_in_pixels,
                   BLACK
    );
}

auto flash_gems() -> void
{
    if (flash_gems_count % 2 == 0)
        for (auto& connector: destroyed_gems)
            for (auto& gem: connector)
                DrawRectangle(
                               get_gem_x_coord(gem->get_x()),
                               get_gem_y_coord(gem->get_y()),
                               settings::square_size,
                               settings::square_size,
                               BLACK );
    else
        draw_blob(&destroyed_gems);
    flash_gems_count--;
    _sleep(100);
    if (flash_gems_count == 0) destroyed_gems.clear();
}

bool cascading = false;

Game game;

auto pause() -> void
{
    if (game.game_is_paused())
        game.set_status(ACTIVE);
    else game.set_status(PAUSED);
}

std::map<int, std::function<void()>> controls
{
    { KEY_A, [](){ game.set_gemstack_orientation( LEFT ); } },
    { KEY_S, [](){ game.set_gemstack_orientation( RIGHT ); } },
    { KEY_SPACE, pause },
    { KEY_Z, [](){ game.set_gemstack_orientation( DOWN ); } },
    { KEY_R, [](){ game.rotate_gemstack(); } },
    { KEY_LEFT, [](){ game.shift_gemstack_left(); } },
    { KEY_RIGHT, [](){ game.shift_gemstack_right(); } }
};

int main()
{
    InitWindow(settings::window_width,
               settings::window_height,
               "Gems");
    SetTargetFPS(4);

    while ( !WindowShouldClose() )
    {
        game.advance_game();

        BeginDrawing();
        ClearBackground(GRAY);

        draw_board();
        draw_points_count(game.get_current_score());
        draw_blob(game.get_blob());
        draw_gemstack(game.get_current_gemstack());

        EndDrawing();

        for (auto& [key, value]: controls)
            if (IsKeyDown(key))
                value();
    }
    CloseWindow();
}
#endif
