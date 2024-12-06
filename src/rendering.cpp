#include "rendering.h"
#include "colors.h"

auto load_textures() -> void
{
    Image image;
    for ( auto image_name : images ) {
        image = LoadImage( ( path + image_name + extension ).c_str() );
        textures[ image_name ] = LoadTextureFromImage( image );
        UnloadImage( image );
    }
}

auto get_next_gems_y_offset(const int i) -> unsigned {
    return settings::next_gems_y_offset + i * settings::square_size;
}

auto get_next_gems_offset(const int i) -> Vector2 {
    return Vector2{ settings::next_gems_x_offset,
                     settings::next_gems_y_offset + i * settings::square_size + settings::square_size / 2 };
}

auto draw_next_gems(const gemstack_colors_t next_colors) -> void
{
    DrawRectangle( settings::next_gems_container_x_offset,
                   settings::next_gems_y_offset,
                   settings::square_size,
                   settings::square_size *
                   settings::gems_in_gemstack,
                   BLACK );

    for ( int i = 0; i < settings::gems_in_gemstack; i++ ) {
        const y_t y = get_next_gems_y_offset( i );
        switch ( next_colors[ i ] ){
            case YELLOW_C:
                DrawTexture( textures["topaz"], settings::next_gems_x_offset, y, WHITE );
                break;
            case BLUE_C:
                DrawTexture( textures["sapphire"], settings::next_gems_x_offset, y, WHITE );
                break;
            case GREEN_C:
                DrawTexture( textures["emerald"], settings::next_gems_x_offset, y, WHITE );
                break;
            case ORANGE_C:
                DrawTexture( textures["citrine"], settings::next_gems_x_offset, y, WHITE );
                break;
            case RED_C:
                DrawTexture( textures["ruby"], settings::next_gems_x_offset, y, WHITE );
                break;
            default: break;
        }
    }
}

auto draw_gem(const gem_raw_ptr gem) -> void
{
    if ( gem->get_y() < 0 )
        return;
    const x_t x = get_gem_x_coord(gem->get_x());
    const y_t y = get_gem_y_coord(gem->get_y());
    switch (gem->get_color()){
        case YELLOW_C:
            DrawTexture( textures["topaz"], x, y, WHITE );
            break;
        case BLUE_C:
            DrawTexture( textures["sapphire"], x, y, WHITE );
            break;
        case GREEN_C:
            DrawTexture( textures["emerald"], x, y, WHITE );
            break;
        case ORANGE_C:
            DrawTexture( textures["citrine"], x, y, WHITE );
            break;
        case RED_C:
            DrawTexture( textures["ruby"], x, y, WHITE );
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
    for ( int i = 0; i <= settings::board_width; i++ )
        for ( int j = 0; j <= settings::board_height; j++ )
            DrawTexture( textures["board_square"],
                         settings::board_x_offset + i * settings::square_size,
                         settings::board_y_offset + j * settings::square_size,
                         WHITE );
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
    for ( int i = 0; i < 14; i++ )
        for ( int j = 0; j < 20; j++ ) {
            const x_t x = j * settings::square_size;
            const y_t y = i * settings::square_size;
            if ( i % 2 == 0 )
                if ( j % 2 == 1 )
                    DrawTexture( textures["green_tile"], x, y, WHITE );
                else
                    DrawTexture( textures["blue_tile"], x, y, WHITE );
            else
                if ( j % 2 == 1 )
                    DrawTexture( textures["blue_tile"], x, y, WHITE );
                else
                    DrawTexture( textures["green_tile"], x, y, WHITE );
        }
}


