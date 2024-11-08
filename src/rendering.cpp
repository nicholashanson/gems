#include "rendering.h"

auto draw_next_gems(const gemstack_colors_t next_colors) -> void
{
    DrawRectangle( settings::next_gems_x_offset,
                   settings::next_gems_y_offset,
                   settings::square_size,
                   settings::square_size *
                   settings::gems_in_gemstack,
                   BLACK );
    for ( int i = 0; i < settings::gems_in_gemstack; i++ ) {
        Rectangle rec = { settings::next_gems_x_offset,
                          settings::next_gems_y_offset +
                          i * settings::square_size,
                          settings::square_size,
                          settings::square_size };
        switch ( next_colors[ i ] ){
            case YELLOW_C:
                DrawPoly( Vector2{ settings::next_gems_x_offset +
                            settings::square_size / 2,
                            settings::next_gems_y_offset +
                            i * settings::square_size +
                            settings::square_size / 2 },
                          6,
                          settings::square_size / 2,
                          90,
                          YELLOW);
                break;
            case BLUE_C:
                DrawRectangleRounded( rec, 0.2f, 0, BLUE);
                break;
            case GREEN_C:
                DrawPoly( Vector2{ settings::next_gems_x_offset +
                            settings::square_size / 2,
                            settings::next_gems_y_offset +
                            i * settings::square_size +
                            settings::square_size / 2 },
                          8,
                          settings::square_size / 2,
                          360/16,
                          GREEN);
                break;
            case ORANGE_C:
                DrawPoly( Vector2{ settings::next_gems_x_offset +
                            settings::square_size / 2,
                            settings::next_gems_y_offset +
                            i * settings::square_size +
                            settings::square_size / 2},
                          6,
                          settings::square_size / 2,
                          0,
                          ORANGE);
                break;
            case RED_C:
                DrawCircle( settings::next_gems_x_offset +
                            settings::square_size / 2,
                            settings::next_gems_y_offset +
                            i * settings::square_size +
                            settings::square_size / 2,
                            settings::gem_radius,
                            RED );
                break;
            default: break;
        }
    }
}

auto draw_gem(const gem_raw_ptr gem) -> void
{
    if ( gem->get_y() < 0 )
        return;
    Rectangle rec = {
        get_gem_x_coord(gem->get_x()),
        get_gem_y_coord(gem->get_y()),
        settings::square_size,
        settings::square_size
    };
    switch (gem->get_color()){
        case YELLOW_C:
            DrawPoly( Vector2{
                        get_gem_x_coord(gem->get_x()) +
                        settings::square_size / 2,
                        get_gem_y_coord(gem->get_y()) +
                        settings::square_size / 2 },
                      6,
                      settings::square_size / 2,
                      90,
                      YELLOW);
            break;
        case BLUE_C:
            DrawRectangleRounded( rec, 0.2f, 0, BLUE);
            break;
        case GREEN_C:
            DrawPoly( Vector2{ get_gem_x_coord(gem->get_x()) +
                        settings::square_size / 2,
                        get_gem_y_coord(gem->get_y()) +
                        settings::square_size / 2},
                      8,
                      settings::square_size / 2,
                      360/16,
                      GREEN);
            break;
        case ORANGE_C:
            DrawPoly( Vector2{ get_gem_x_coord(gem->get_x()) +
                        settings::square_size / 2,
                        get_gem_y_coord(gem->get_y()) +
                        settings::square_size / 2},
                      6,
                      settings::square_size / 2,
                      0,
                      ORANGE);
            break;
        case RED_C:
            DrawCircle( get_gem_x_coord(gem->get_x()) +
                        settings::square_size / 2,
                        get_gem_y_coord(gem->get_y()) +
                        settings::square_size / 2,
                        settings::gem_radius,
                        RED );
            break;
        default: break;
    }
}

auto draw_blob(const blob_t* blob) -> void
{
    for ( const connector_t& connector: *blob )
        if ( connector.size() >= settings::gems_to_connect )
            for ( const gem_uptr& gem: connector)
                DrawRectangle( get_gem_x_coord(gem->get_x()),
                               get_gem_y_coord(gem->get_y()),
                               settings::square_size,
                               settings::square_size,
                               WHITE );
        else
            for (auto& gem: connector)
                draw_gem(gem.get());
}

auto draw_points_count(const score_t current_score) -> void
{
   DrawRectangle( settings::points_count_x_offset,
                  settings::points_count_y_offset,
                  settings::points_count_width,
                  settings::square_size,
                  BLACK );
   DrawText( TextFormat( "Score: %03i", current_score ),
             settings::points_count_x_offset +
             settings::text_x_offset,
             settings::points_count_y_offset +
             settings::text_y_offset,
             20,
             WHITE );
}

auto get_gem_x_coord(const int i) -> int
{
    return i*settings::square_size + settings::board_x_offset;
}

auto get_gem_y_coord(const int j) -> int
{
    return j*settings::square_size + settings::board_y_offset;
}

auto draw_gemstack(GemStack* gemstack) -> void
{
    for ( const gem_uptr& gem: *( gemstack->get_gems() ) )
        draw_gem( gem.get() );
}

auto draw_board() -> void
{
    DrawRectangle( settings::board_x_offset,
                   settings::board_y_offset,
                   settings::board_width_in_pixels,
                   settings::board_height_in_pixels,
                   BLACK );
}

auto flash_gems() -> void
{
    if (flash_gems_count % 2 == 0)
        for ( const connector_t& connector: destroyed_gems )
            for ( const gem_uptr& gem: connector)
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

auto draw_background() -> void
{
    for ( int i = 0; i < 7; i++ )
        for ( int j = 0; j < 10; j++ )
            if ( i % 2 == 0 )
                if ( j % 2 == 1 )
                    DrawRectangle(
                        j*settings::square_size*2,
                        i*settings::square_size*2,
                        settings::square_size*2,
                        settings::square_size*2,
                        BLUE
                    );
                else
                     DrawRectangle(
                        j*settings::square_size*2,
                        i*settings::square_size*2,
                        settings::square_size*2,
                        settings::square_size*2,
                        GREEN
                    );
            else
                if ( j % 2 == 1 )
                    DrawRectangle(
                        j*settings::square_size*2,
                        i*settings::square_size*2,
                        settings::square_size*2,
                        settings::square_size*2,
                        GREEN
                    );
                else
                     DrawRectangle(
                        j*settings::square_size*2,
                        i*settings::square_size*2,
                        settings::square_size*2,
                        settings::square_size*2,
                        BLUE
                    );
}


