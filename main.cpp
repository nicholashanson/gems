#ifndef TEST
#include "Game.h"
#include "raylib.h"
#include "rendering.h"

Game game;

auto pause() -> void
{
    if ( game.game_is_paused() )
        game.set_status( ACTIVE );
    else game.set_status( PAUSED );
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

    InitWindow( settings::window_width,
                settings::window_height,
                "Gems" );

    load_textures();

    SetTargetFPS(4);

    while ( !WindowShouldClose() )
    {
        game.advance_game();

        BeginDrawing();

        // drawing must be in this order:
        // background -> board -> blob/gemstack
        // background -> next_gems
        // background -> points_count
        draw_background();

        draw_board();

        draw_points_count( game.get_current_score() );
        draw_next_gems( game.get_next_gemstack_colors() );

        draw_blob( game.get_blob() );
        draw_gemstack( game.get_current_gemstack() );

        EndDrawing();

        // check for plater input
        for ( auto& [key, value]: controls )
            if ( IsKeyDown( key ) )
                value();
    }
    CloseWindow();
}
#endif
