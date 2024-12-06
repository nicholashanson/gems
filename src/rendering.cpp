#include "rendering.h"
#include "colors.h"

auto load_textures() -> void
{
    Image ruby_image = LoadImage( "ruby.png" );
    Image sapphire_image = LoadImage( "sapphire.png" );
    Image citrine_image = LoadImage( "citrine.png" );
    Image topaz_image = LoadImage( "topaz.png" );
    Image emerald_image = LoadImage( "emerald.png" );
    Image green_tile_image = LoadImage( "green_tile.png" );
    Image blue_tile_image = LoadImage( "blue_tile.png" );
    Image board_square_image = LoadImage( "board_square.png" );
    ruby_texture = LoadTextureFromImage( ruby_image );
    sapphire_texture = LoadTextureFromImage( sapphire_image );
    citrine_texture = LoadTextureFromImage( citrine_image );
    topaz_texture = LoadTextureFromImage( topaz_image );
    emerald_texture = LoadTextureFromImage( emerald_image );
    green_tile_texture = LoadTextureFromImage( green_tile_image );
    blue_tile_texture = LoadTextureFromImage( blue_tile_image );
    board_square_texture = LoadTextureFromImage( board_square_image );
    UnloadImage( ruby_image );
    UnloadImage( sapphire_image );
    UnloadImage( citrine_image );
    UnloadImage( topaz_image );
    UnloadImage( emerald_image );
    UnloadImage( green_tile_image );
    UnloadImage( blue_tile_image );
    UnloadImage( board_square_image );
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
                DrawTexture( topaz_texture, settings::next_gems_x_offset, y, WHITE );
                break;
            case BLUE_C:
                DrawTexture( sapphire_texture, settings::next_gems_x_offset, y, WHITE );
                break;
            case GREEN_C:
                DrawTexture( emerald_texture, settings::next_gems_x_offset, y, WHITE );
                break;
            case ORANGE_C:
                DrawTexture( citrine_texture, settings::next_gems_x_offset, y, WHITE );
                break;
            case RED_C:
                DrawTexture( ruby_texture, settings::next_gems_x_offset, y, WHITE );
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
            DrawTexture( topaz_texture, x, y, WHITE );
            break;
        case BLUE_C:
            DrawTexture( sapphire_texture, x, y, WHITE );
            break;
        case GREEN_C:
            DrawTexture( emerald_texture, x, y, WHITE );
            break;
        case ORANGE_C:
            DrawTexture( citrine_texture, x, y, WHITE );
            break;
        case RED_C:
            DrawTexture( ruby_texture, x, y, WHITE );
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
            DrawTexture( board_square_texture,
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
                    DrawTexture( green_tile_texture, x, y, WHITE );
                else
                    DrawTexture( blue_tile_texture, x, y, WHITE );
            else
                if ( j % 2 == 1 )
                    DrawTexture( blue_tile_texture, x, y, WHITE );
                else
                    DrawTexture( green_tile_texture, x, y, WHITE );
        }
}


