#ifdef TEST
#define BOOST_TEST_MODULE TestSuite
#include <boost/test/included/unit_test.hpp>
#include "Game.h"

BOOST_AUTO_TEST_CASE(SettingsTest)
{
    BOOST_CHECK(settings::board_width > 0);
    BOOST_CHECK(settings::board_height > 0);
}

BOOST_AUTO_TEST_CASE(GemLengthTest)
{
    Game game;
    BOOST_CHECK_EQUAL(game.get_current_gemstack()->gemstack_length(), 3);
}

BOOST_AUTO_TEST_CASE(SwapColorsTest)
{
    Game game;
    color_t first_before = game.get_current_gemstack()->get_first_gem()->get_color();
    color_t middle_before = game.get_current_gemstack()->get_middle_gem()->get_color();
    swap_colors( game.get_current_gemstack()->get_first_gem(),
                                 game.get_current_gemstack()->get_middle_gem() );
    BOOST_CHECK_EQUAL(game.get_current_gemstack()->get_first_gem()->get_color(), middle_before);
    BOOST_CHECK_EQUAL(game.get_current_gemstack()->get_middle_gem()->get_color(), first_before);
    swap_colors( game.get_current_gemstack()->get_first_gem(),
                                 game.get_current_gemstack()->get_middle_gem());
    BOOST_CHECK_EQUAL(game.get_current_gemstack()->get_first_gem()->get_color(), first_before);
    BOOST_CHECK_EQUAL(game.get_current_gemstack()->get_middle_gem()->get_color(), middle_before);
}

BOOST_AUTO_TEST_CASE(RotateGemTest)
{
    Game game;
    color_t first_before = game.get_current_gemstack()->get_first_gem()->get_color();
    color_t middle_before = game.get_current_gemstack()->get_middle_gem()->get_color();
    color_t last_before = game.get_current_gemstack()->get_last_gem()->get_color();
    game.rotate_gemstack();
    color_t first_after = game.get_current_gemstack()->get_first_gem()->get_color();
    color_t middle_after = game.get_current_gemstack()->get_middle_gem()->get_color();
    color_t last_after = game.get_current_gemstack()->get_last_gem()->get_color();
    BOOST_CHECK_EQUAL( first_before, last_after );
    BOOST_CHECK_EQUAL( middle_before, first_after );
    BOOST_CHECK_EQUAL( last_before, middle_after );
}

BOOST_AUTO_TEST_CASE(GemInitialOrientationTest)
{
    Game game;
    BOOST_CHECK_EQUAL(game.get_gemstack_orientation(), UP);
}

BOOST_AUTO_TEST_CASE(OrientationShuffleTest)
{
    Game game;
    game.toggle_gemstack_orientation();
    BOOST_CHECK_EQUAL(game.get_gemstack_orientation(), RIGHT);
    game.toggle_gemstack_orientation();
    BOOST_CHECK_EQUAL(game.get_gemstack_orientation(), DOWN);
    game.toggle_gemstack_orientation();
    BOOST_CHECK_EQUAL(game.get_gemstack_orientation(), LEFT);
    game.toggle_gemstack_orientation();
    BOOST_CHECK_EQUAL(game.get_gemstack_orientation(), UP);
}

BOOST_AUTO_TEST_CASE(InitialYTest)
{
    Game game;
    BOOST_CHECK_EQUAL(game.get_first_y(), settings::first_starting_y);
    BOOST_CHECK_EQUAL(game.get_middle_y(), settings::middle_starting_y);
    BOOST_CHECK_EQUAL(game.get_last_y(), settings::last_starting_y);
}

BOOST_AUTO_TEST_CASE(InitialXTest)
{
    Game game;
    BOOST_CHECK_EQUAL(game.get_first_x(), settings::board_middle);
    BOOST_CHECK_EQUAL(game.get_middle_x(), settings::board_middle);
    BOOST_CHECK_EQUAL(game.get_last_x(), settings::board_middle);
}

BOOST_AUTO_TEST_CASE(AdvanceGemStackTest)
{
    Game game;
    game.advance_gemstack();
    BOOST_CHECK_EQUAL(game.get_first_y(), settings::first_starting_y+1);
    BOOST_CHECK_EQUAL(game.get_middle_y(), settings::middle_starting_y+1);
    BOOST_CHECK_EQUAL(game.get_last_y(), settings::last_starting_y+1);
}

BOOST_AUTO_TEST_CASE(ShiftRightTest)
{
    Game game;
    game.shift_gemstack_right();
    BOOST_CHECK_EQUAL(game.get_first_x(), settings::board_middle+1);
    BOOST_CHECK_EQUAL(game.get_middle_x(), settings::board_middle+1);
    BOOST_CHECK_EQUAL(game.get_last_x(), settings::board_middle+1);
}

BOOST_AUTO_TEST_CASE(ShiftLeftTest)
{
    Game game;
    game.shift_gemstack_left();
    BOOST_CHECK_EQUAL(game.get_first_x(), settings::board_middle-1);
    BOOST_CHECK_EQUAL(game.get_middle_x(), settings::board_middle-1);
    BOOST_CHECK_EQUAL(game.get_last_x(), settings::board_middle-1);
}

BOOST_AUTO_TEST_CASE(RightOrientationShiftRightTest)
{
    Game game;
    game.set_gemstack_orientation(RIGHT);
    game.shift_gemstack_right();
    BOOST_CHECK_EQUAL(game.get_first_x(), settings::board_middle+2);
    BOOST_CHECK_EQUAL(game.get_middle_x(), settings::board_middle+1);
    BOOST_CHECK_EQUAL(game.get_last_x(), settings::board_middle);
}

BOOST_AUTO_TEST_CASE(RightOrientationShiftLeftTest)
{
    Game game;
    game.set_gemstack_orientation(RIGHT);
    game.shift_gemstack_left();
    BOOST_CHECK_EQUAL(game.get_first_x(), settings::board_middle);
    BOOST_CHECK_EQUAL(game.get_middle_x(), settings::board_middle-1);
    BOOST_CHECK_EQUAL(game.get_last_x(), settings::board_middle-2);
}

BOOST_AUTO_TEST_CASE(DownOrientationShiftLeftTest)
{
    Game game;
    game.set_gemstack_orientation(DOWN);
    game.shift_gemstack_left();
    BOOST_CHECK_EQUAL(game.get_first_x(), settings::board_middle-1);
    BOOST_CHECK_EQUAL(game.get_middle_x(), settings::board_middle-1);
    BOOST_CHECK_EQUAL(game.get_last_x(), settings::board_middle-1);
}

BOOST_AUTO_TEST_CASE(DownOrientationShiftRightTest)
{
    Game game;
    game.set_gemstack_orientation(DOWN);
    game.shift_gemstack_right();
    BOOST_CHECK_EQUAL(game.get_first_x(), settings::board_middle+1);
    BOOST_CHECK_EQUAL(game.get_middle_x(), settings::board_middle+1);
    BOOST_CHECK_EQUAL(game.get_last_x(), settings::board_middle+1);
}

BOOST_AUTO_TEST_CASE(LeftOrientationShiftLeftTest)
{
    Game game;
    game.set_gemstack_orientation(LEFT);
    game.shift_gemstack_left();
    BOOST_CHECK_EQUAL(game.get_last_x(), settings::board_middle);
    BOOST_CHECK_EQUAL(game.get_middle_x(), settings::board_middle-1);
    BOOST_CHECK_EQUAL(game.get_first_x(), settings::board_middle-2);
}

BOOST_AUTO_TEST_CASE(LeftOrientationShiftRightTest)
{
    Game game;
    game.set_gemstack_orientation(LEFT);
    game.shift_gemstack_right();
    BOOST_CHECK_EQUAL(game.get_first_x(), settings::board_middle);
    BOOST_CHECK_EQUAL(game.get_middle_x(), settings::board_middle+1);
    BOOST_CHECK_EQUAL(game.get_last_x(), settings::board_middle+2);
}

BOOST_AUTO_TEST_CASE(SweepRightTest)
{
    Game game;
    BOOST_CHECK_EQUAL( game.__measure_distance_to_right_blocking_gem(),
                       settings::board_width - settings::board_middle );
    game.sweep_gemstack_right();
    BOOST_CHECK_EQUAL(game.get_first_x(), settings::board_width);
    BOOST_CHECK_EQUAL(game.get_middle_x(), settings::board_width);
    BOOST_CHECK_EQUAL(game.get_last_x(), settings::board_width);
}

BOOST_AUTO_TEST_CASE(SweepLeftTest)
{
    Game game;
    game.sweep_gemstack_left();
    BOOST_CHECK_EQUAL(game.get_first_x(), 0);
    BOOST_CHECK_EQUAL(game.get_middle_x(), 0);
    BOOST_CHECK_EQUAL(game.get_last_x(), 0);
}

BOOST_AUTO_TEST_CASE(RightOrientationSweepRightTest)
{
    Game game;
    game.set_gemstack_orientation(RIGHT);
    game.sweep_gemstack_right();
    BOOST_CHECK_EQUAL(game.get_first_x(), settings::board_width);
    BOOST_CHECK_EQUAL(game.get_middle_x(), settings::board_width-1);
    BOOST_CHECK_EQUAL(game.get_last_x(), settings::board_width-2);
}

BOOST_AUTO_TEST_CASE(RightOrientationSweepLeftTest)
{
    Game game;
    game.set_gemstack_orientation(RIGHT);
    game.sweep_gemstack_left();
    BOOST_CHECK_EQUAL(game.get_last_x(), 0);
    BOOST_CHECK_EQUAL(game.get_middle_x(), 1);
    BOOST_CHECK_EQUAL(game.get_first_x(), 2);
}

BOOST_AUTO_TEST_CASE(DownOrientationSweepRightTest)
{
    Game game;
    game.set_gemstack_orientation(DOWN);
    game.sweep_gemstack_right();
    BOOST_CHECK_EQUAL(game.get_last_x(), settings::board_width);
    BOOST_CHECK_EQUAL(game.get_middle_x(), settings::board_width);
    BOOST_CHECK_EQUAL(game.get_first_x(), settings::board_width);
}

BOOST_AUTO_TEST_CASE(DownOrientationSweepLeftTest)
{
    Game game;
    game.set_gemstack_orientation(DOWN);
    game.sweep_gemstack_left();
    BOOST_CHECK_EQUAL(game.get_last_x(), 0);
    BOOST_CHECK_EQUAL(game.get_middle_x(), 0);
    BOOST_CHECK_EQUAL(game.get_first_x(), 0);
}

BOOST_AUTO_TEST_CASE(LeftOrientationSweepLeftTest)
{
    Game game;
    game.set_gemstack_orientation(LEFT);
    game.sweep_gemstack_left();
    BOOST_CHECK_EQUAL(game.get_first_x(), 0);
    BOOST_CHECK_EQUAL(game.get_middle_x(), 1);
    BOOST_CHECK_EQUAL(game.get_last_x(), 2);
}

BOOST_AUTO_TEST_CASE(LeftOrientationSweepRightTest)
{
    Game game;
    game.set_gemstack_orientation(LEFT);
    game.sweep_gemstack_right();
    BOOST_CHECK_EQUAL(game.get_last_x(), settings::board_width);
    BOOST_CHECK_EQUAL(game.get_middle_x(), settings::board_width-1);
    BOOST_CHECK_EQUAL(game.get_first_x(), settings::board_width-2);
}

BOOST_AUTO_TEST_CASE(LeftSideUpRightOrientationTest)
{
    Game game;
    game.sweep_gemstack_left();
    game.set_gemstack_orientation(RIGHT);
    BOOST_CHECK_EQUAL(game.get_last_x(), 0);
    BOOST_CHECK_EQUAL(game.get_middle_x(), 1);
    BOOST_CHECK_EQUAL(game.get_first_x(), 2);
}

BOOST_AUTO_TEST_CASE(LeftSideUpLeftOrientationTest)
{
    Game game;
    game.sweep_gemstack_left();
    game.set_gemstack_orientation(LEFT);
    BOOST_CHECK_EQUAL(game.get_first_x(), 0);
    BOOST_CHECK_EQUAL(game.get_middle_x(), 1);
    BOOST_CHECK_EQUAL(game.get_last_x(), 2);
}

BOOST_AUTO_TEST_CASE(LeftSideDownRightOrientationTest)
{
    Game game;
    game.sweep_gemstack_left();
    game.set_gemstack_orientation(RIGHT);
    BOOST_CHECK_EQUAL(game.get_last_x(), 0);
    BOOST_CHECK_EQUAL(game.get_middle_x(), 1);
    BOOST_CHECK_EQUAL(game.get_first_x(), 2);
}

BOOST_AUTO_TEST_CASE(LeftSideDownLeftOrientationTest)
{
    Game game;
    game.set_gemstack_orientation(DOWN);
    game.sweep_gemstack_left();
    game.set_gemstack_orientation(LEFT);
    BOOST_CHECK_EQUAL(game.get_first_x(), 0);
    BOOST_CHECK_EQUAL(game.get_middle_x(), 1);
    BOOST_CHECK_EQUAL(game.get_last_x(), 2);
}

BOOST_AUTO_TEST_CASE(RightSideUpRightOrientationTest)
{
    Game game;
    game.set_gemstack_orientation(DOWN);
    game.sweep_gemstack_right();
    game.set_gemstack_orientation(RIGHT);
    BOOST_CHECK_EQUAL(game.get_first_x(), settings::board_width);
    BOOST_CHECK_EQUAL(game.get_middle_x(), settings::board_width-1);
    BOOST_CHECK_EQUAL(game.get_last_x(), settings::board_width-2);
}

BOOST_AUTO_TEST_CASE(RightSideUpLeftOrientationTest)
{
    Game game;
    game.sweep_gemstack_right();
    game.set_gemstack_orientation(LEFT);
    BOOST_CHECK_EQUAL(game.get_last_x(), settings::board_width);
    BOOST_CHECK_EQUAL(game.get_middle_x(), settings::board_width-1);
    BOOST_CHECK_EQUAL(game.get_first_x(), settings::board_width-2);
}

BOOST_AUTO_TEST_CASE(RightSideDownRightOrientationTest)
{
    Game game;
    game.set_gemstack_orientation(DOWN);
    game.sweep_gemstack_right();
    game.set_gemstack_orientation(RIGHT);
    BOOST_CHECK_EQUAL(game.get_first_x(), settings::board_width);
    BOOST_CHECK_EQUAL(game.get_middle_x(), settings::board_width-1);
    BOOST_CHECK_EQUAL(game.get_last_x(), settings::board_width-2);
}

BOOST_AUTO_TEST_CASE(RightSideDownLeftOrientationTest)
{
    Game game;
    game.set_gemstack_orientation(DOWN);
    game.sweep_gemstack_right();
    game.set_gemstack_orientation(LEFT);
    BOOST_CHECK_EQUAL(game.get_last_x(), settings::board_width);
    BOOST_CHECK_EQUAL(game.get_middle_x(), settings::board_width-1);
    BOOST_CHECK_EQUAL(game.get_first_x(), settings::board_width-2);
}

BOOST_AUTO_TEST_CASE(SetOrientationTest)
{
    Game game;
    game.set_gemstack_orientation(RIGHT);
    BOOST_CHECK_EQUAL(game.get_gemstack_orientation(), RIGHT);
    game.set_gemstack_orientation(DOWN);
    BOOST_CHECK_EQUAL(game.get_gemstack_orientation(), DOWN);
    game.set_gemstack_orientation(LEFT);
    BOOST_CHECK_EQUAL(game.get_gemstack_orientation(), LEFT);
    game.set_gemstack_orientation(UP);
    BOOST_CHECK_EQUAL(game.get_gemstack_orientation(), UP);
}

BOOST_AUTO_TEST_CASE(BoardRightXLimitTest)
{
    Game game;
    game.sweep_gemstack_right();
    game.shift_gemstack_right();
    BOOST_CHECK_EQUAL(game.get_first_x(), settings::board_width);
}

BOOST_AUTO_TEST_CASE(BoardLeftXLimitTest)
{
    Game game;
    game.sweep_gemstack_left();
    game.shift_gemstack_left();
    BOOST_CHECK_EQUAL(game.get_first_x(), 0);
}

BOOST_AUTO_TEST_CASE(BlobSizeTest)
{
    Game game;
    game.generate_test_blob();
    BOOST_CHECK_EQUAL(game.count_gems_in_blob(),
                      settings::board_size);
}

BOOST_AUTO_TEST_CASE(AddGemToBlobTest)
{
    Game game;
    game.add_gem_to_blob( std::make_unique<Gem>(
                          RED_C,
                          settings::board_width,
                          settings::board_height ) );
    BOOST_CHECK_EQUAL(game.count_gems_in_blob(), 1);
    BOOST_CHECK_EQUAL(game.count_connectors_in_blob(), 1);
    game.add_gem_to_blob( std::make_unique<Gem>(
                          RED_C,
                          settings::board_width - 1,
                          settings::board_height ) );
    BOOST_CHECK_EQUAL(game.count_gems_in_blob(), 2);
    BOOST_CHECK_EQUAL(game.count_connectors_in_blob(), 1);
    game.add_gem_to_blob( std::make_unique<Gem>(
                          RED_C,
                          settings::board_width - 2,
                          settings::board_height ) );
    BOOST_CHECK_EQUAL(game.count_gems_in_blob(), 3);
    BOOST_CHECK_EQUAL(game.count_connectors_in_blob(), 1);
    game.add_gem_to_blob( std::make_unique<Gem>(
                          RED_C,
                          settings::board_width - 3,
                          settings::board_height ) );
    BOOST_CHECK_EQUAL(game.count_gems_in_blob(), 4);
    BOOST_CHECK_EQUAL(game.count_connectors_in_blob(), 1);
    game.add_gem_to_blob( std::make_unique<Gem>(
                          BLUE_C,
                          settings::board_width - 4,
                          settings::board_height ) );
    BOOST_CHECK_EQUAL(game.count_gems_in_blob(), 5);
    BOOST_CHECK_EQUAL(game.count_connectors_in_blob(), 2);
    game.add_gem_to_blob( std::make_unique<Gem>(
                          RED_C,
                          settings::board_width - 4,
                          settings::board_height - 1) );
    BOOST_CHECK_EQUAL(game.count_gems_in_blob(), 6);
    BOOST_CHECK_EQUAL(game.count_connectors_in_blob(), 3);
    game.add_gem_to_blob( std::make_unique<Gem>(
                          RED_C,
                          settings::board_width - 3,
                          settings::board_height - 1) );
    BOOST_CHECK_EQUAL(game.count_gems_in_blob(), 7);
    BOOST_CHECK_EQUAL(game.count_connectors_in_blob(), 2);
    BOOST_CHECK_EQUAL(game.get_blob()->operator[](0).size(), 6);
}

BOOST_AUTO_TEST_CASE(ConvertBlobToGridTest)
{
    Game game;
    game.add_gem_to_blob( std::make_unique<Gem>(
                          RED_C,
                          settings::board_width,
                          settings::board_height ) );
    game.add_gem_to_blob( std::make_unique<Gem>(
                          RED_C,
                          settings::board_width - 1,
                          settings::board_height ) );
    game.add_gem_to_blob( std::make_unique<Gem>(
                          RED_C,
                          settings::board_width - 2,
                          settings::board_height ) );
    game.add_gem_to_blob( std::make_unique<Gem>(
                          BLUE_C,
                          settings::board_width,
                          settings::board_height - 1 ) );
    game.add_gem_to_blob( std::make_unique<Gem>(
                          BLUE_C,
                          settings::board_width - 1,
                          settings::board_height - 1 ) );
    game.add_gem_to_blob( std::make_unique<Gem>(
                          GREEN_C,
                          settings::board_width - 2,
                          settings::board_height - 1 ) );
    game.add_gem_to_blob( std::make_unique<Gem>(
                          GREEN_C,
                          settings::board_width,
                          settings::board_height - 2 ) );
    game.add_gem_to_blob( std::make_unique<Gem>(
                          GREEN_C,
                          settings::board_width - 1,
                          settings::board_height - 2 ) );
    game.add_gem_to_blob( std::make_unique<Gem>(
                          GREEN_C,
                          settings::board_width - 2,
                          settings::board_height - 2 ) );
    game.add_gem_to_blob( std::make_unique<Gem>(
                          YELLOW_C,
                          settings::board_width,
                          settings::board_height - 3 ) );
    BOOST_CHECK_EQUAL(game.count_gems_of_color(BLUE_C), 2);
    BOOST_CHECK_EQUAL(game.count_gems_of_color(YELLOW_C), 1);
    BOOST_CHECK_EQUAL(game.count_connectors_in_blob(), 4);
    BOOST_CHECK_EQUAL(game.count_connectors_to_destroy(), 2);
    BOOST_CHECK_EQUAL(game.count_gems_to_destroy(), 7);
    game.destroy_blob_connectors();
    BOOST_CHECK_EQUAL(game.count_connectors_in_blob(), 2);
    game.convert_blob_to_grid();
    BOOST_CHECK_EQUAL(game.count_columns_in_grid(), 2);
    BOOST_CHECK_EQUAL(game.get_grid()->operator[](settings::board_width).size(), 2);
    BOOST_CHECK_EQUAL(game.get_grid()->operator[](settings::board_width-1).size(), 1);
    BOOST_CHECK_EQUAL(game.get_grid()->operator[](settings::board_width).front()->get_x(),
                                                    settings::board_width);
    BOOST_CHECK_EQUAL(game.get_grid()->operator[](settings::board_width).front()->get_y(),
                                                    settings::board_height-1);
    BOOST_CHECK_EQUAL(game.get_grid()->operator[](settings::board_width)[1]->get_y(),
                                                    settings::board_height-3);

    game.cascade_grid();
    BOOST_CHECK_EQUAL(game.get_grid()->operator[](settings::board_width).front()->get_y(),
                                                    settings::board_height);
    BOOST_CHECK_EQUAL(game.get_grid()->operator[](settings::board_width)[1]->get_y(),
                                                    settings::board_height-2);
    BOOST_CHECK_EQUAL(game.count_gems_in_grid(), 3);
}

BOOST_AUTO_TEST_CASE(DeleteConnectorTest)
{
    Game game;
    game.generate_test_blob();
    count_t total_connectors = game.count_connectors_in_blob();
    count_t connectors_for_destruction = game.count_connectors_to_destroy();
    game.destroy_blob_connectors();
    BOOST_CHECK_EQUAL( total_connectors,
                       game.count_connectors_in_blob() + connectors_for_destruction );
}

BOOST_AUTO_TEST_CASE(LongestConnectorTest)
{
    Game game;
    game.generate_test_blob();
    game.destroy_blob_connectors();
    BOOST_CHECK_LT( game.measure_longest_connector(), settings::gems_to_connect );
}

BOOST_AUTO_TEST_CASE(PopulateGemstackColorTest)
{
    Game game;
    game.add_current_gemstack_to_blob();
    game.get_current_gemstack()->populate_gemstack(
                                 game.get_next_gemstack_colors());
   BOOST_CHECK_EQUAL_COLLECTIONS( game.get_current_gemstack()->get_gem_colors().begin(),
                                  game.get_current_gemstack()->get_gem_colors().end(),
                                  game.get_next_gemstack_colors().begin(),
                                  game.get_next_gemstack_colors().end()
                                 );
}

BOOST_AUTO_TEST_CASE(PopulateGemstackXTest)
{
    Game game;
    game.add_current_gemstack_to_blob();
    game.get_current_gemstack()->populate_gemstack(
                                 game.get_next_gemstack_colors());
    BOOST_CHECK_EQUAL(game.get_current_gemstack()->get_first_gem()->get_x(),
                     settings::board_middle);
    BOOST_CHECK_EQUAL(game.get_current_gemstack()->get_middle_gem()->get_x(),
                     settings::board_middle);
    BOOST_CHECK_EQUAL(game.get_current_gemstack()->get_last_gem()->get_x(),
                     settings::board_middle);
}

BOOST_AUTO_TEST_CASE(PopulateGemstackYTest)
{
    Game game;
    game.add_current_gemstack_to_blob();
    game.get_current_gemstack()->populate_gemstack(
                                 game.get_next_gemstack_colors());
    BOOST_CHECK_EQUAL(game.get_current_gemstack()->get_first_gem()->get_y(),
                     settings::first_starting_y);
    BOOST_CHECK_EQUAL(game.get_current_gemstack()->get_middle_gem()->get_y(),
                     settings::middle_starting_y);
    BOOST_CHECK_EQUAL(game.get_current_gemstack()->get_last_gem()->get_y(),
                     settings::last_starting_y);
}

BOOST_AUTO_TEST_CASE(GemStackReachFloorTest)
{
    Game game;
    while ( game.get_current_gemstack()->get_first_gem()->get_y() < settings::board_height )
        game.advance_gemstack();
    BOOST_CHECK_EQUAL(game.get_current_gemstack()->get_first_gem()->get_y(), settings::board_height);
    BOOST_CHECK(game.gemstack_is_at_floor());
    game.add_current_gemstack_to_blob();
    BOOST_CHECK_EQUAL(game.count_gems_in_blob(), 3);
    game.update_floor();
    BOOST_CHECK_EQUAL( game.get_floor()[settings::board_middle],
                       settings::board_height - settings::gems_in_gemstack);
}

BOOST_AUTO_TEST_CASE(CascadeEmptyGridTest)
{
    Game game;
    BOOST_CHECK(!game.cascade_grid());
    game.convert_blob_to_grid();
    BOOST_CHECK(!game.cascade_grid());
    game.advance_gemstack();
    BOOST_CHECK(!game.cascade_grid());
}

BOOST_AUTO_TEST_CASE(StartGameOverTest)
{
    Game game;
    BOOST_CHECK(!game.game_is_over());
}

BOOST_AUTO_TEST_CASE(OverFlowTest)
{
    Game game;
    game.add_gem_layer();
    BOOST_CHECK_EQUAL(game.count_gems_in_blob(), settings::board_width+1);
    BOOST_CHECK_EQUAL(game.get_floor().size(), settings::board_width+1);
    game.update_floor();
    BOOST_CHECK_EQUAL(game.get_floor().size(), settings::board_width+1);
    std::array<int, settings::board_width+1> floor;
    floor.fill(settings::board_height-1);
    floor_t game_floor = game.get_floor();
    BOOST_CHECK_EQUAL_COLLECTIONS( floor.begin(),
                                   floor.end(),
                                   game_floor.begin(),
                                   game_floor.end()
                                  );
    while ( game.get_floor()[0] >= 0) {
        game.add_gem_layer();
        game.update_floor();
    }
    game_floor = game.get_floor();
    BOOST_CHECK(std::all_of(game_floor.begin(), game_floor.end(),
                            [](const auto& y){
                                return -1 == y;
                            }));
    BOOST_CHECK(!game.game_is_over());
    game.add_gem_to_blob(std::make_unique<Gem>(
                         game.get_random_gem_color(),
                         settings::board_middle,
                         -1) );
    game.update_floor();
    BOOST_CHECK(game.game_is_over());
}

BOOST_AUTO_TEST_CASE(RotateGemstackTest)
{
    Game game;
    game.rotate_gemstack();
    BOOST_CHECK_EQUAL(game.get_gemstack_orientation(), UP);
    while ( game.get_current_gemstack()->get_first_gem()->get_y() < settings::board_height)
        game.advance_gemstack();
    BOOST_CHECK_EQUAL(game.get_current_gemstack()->get_first_gem()->get_y(),
                      settings::board_height);
    BOOST_CHECK(game.gemstack_is_at_floor());
    game.add_current_gemstack_to_blob();
    BOOST_CHECK_EQUAL(game.count_gems_in_blob(), settings::gems_in_gemstack);
}

BOOST_AUTO_TEST_CASE(BlobGemColorTest)
{
    Game game;
    for (int i = 0; i < settings::number_of_gem_colors; i++)
        game.add_gem_to_blob(
                             std::make_unique<Gem>(
                                (color_t)i, i, settings::board_height
                             )
                             );
    BOOST_CHECK_EQUAL(game.count_connectors_in_blob(), settings::number_of_gem_colors);
}

BOOST_AUTO_TEST_CASE(CascadeTest)
{
    Game game;
    game.add_gem_to_blob( std::make_unique<Gem>(
                        game.get_random_gem_color(),
                        settings::board_width, settings::board_height));
    game.add_gem_to_blob( std::make_unique<Gem>(
                        game.get_random_gem_color(),
                        settings::board_width, settings::board_height - 5
                                                ));
    game.add_gem_to_blob( std::make_unique<Gem>(
                        game.get_random_gem_color(),
                        settings::board_width, settings::board_height - 2
                                                ));
    game.add_gem_to_blob( std::make_unique<Gem>(
                        game.get_random_gem_color(),
                        settings::board_width, 0
                                                ));
    game.convert_blob_to_grid();
    while (game.cascade_grid()){}
    BOOST_CHECK_EQUAL(game.get_grid()->operator[](settings::board_width).front()->get_y(),
                                                        settings::board_height);
    BOOST_CHECK_EQUAL(game.get_grid()->operator[](settings::board_width)[1]->get_y(),
                                                        settings::board_height-1);
    BOOST_CHECK_EQUAL(game.get_grid()->operator[](settings::board_width)[2]->get_y(),
                                                        settings::board_height-2);
    BOOST_CHECK_EQUAL(game.get_grid()->operator[](settings::board_width)[3]->get_y(),
                                                        settings::board_height-3);
}


BOOST_AUTO_TEST_CASE(RotateGemstackCoordTest)
{
    Game game;
    color_t first_color = first(game.get_current_gemstack_colors());
    game.rotate_gemstack();
    BOOST_CHECK_EQUAL(last(game.get_current_gemstack_colors()), first_color);
}

BOOST_AUTO_TEST_CASE(UpdateFloorTest)
{
    Game game;
    while (!game.gemstack_is_at_floor())
        game.advance_gemstack();
    game.add_current_gemstack_to_blob();
    game.update_floor();
    BOOST_CHECK_EQUAL(game.get_floor()[settings::board_middle],
                      settings::board_height - settings::gems_in_gemstack);
}

BOOST_AUTO_TEST_CASE(ShiftLeftBlockedTest)
{
    Game game;
    while (!game.gemstack_is_at_floor())
        game.advance_gemstack();
    game.add_current_gemstack_to_blob();
    game.update_floor();
    game.update_gemstack();
    game.shift_gemstack_right();
    BOOST_CHECK_EQUAL( game.get_current_gemstack()->get_first_x(),
                settings::board_middle+1 );
    while (!game.gemstack_is_at_floor())
        game.advance_gemstack();
    game.shift_gemstack_left();
    BOOST_CHECK(game.get_current_gemstack()->get_first_x()
                !=settings::board_middle);
}

BOOST_AUTO_TEST_CASE(ShiftRightBlockedTest)
{
    Game game;
    while (!game.gemstack_is_at_floor())
        game.advance_gemstack();
    game.add_current_gemstack_to_blob();
    game.update_floor();
    game.update_gemstack();
    game.shift_gemstack_left();
    while (!game.gemstack_is_at_floor())
        game.advance_gemstack();
    game.shift_gemstack_right();
    BOOST_CHECK(game.get_current_gemstack()->get_first_x()
                !=settings::board_middle);
}

BOOST_AUTO_TEST_CASE(SweepRightBlockedTest)
{
    Game game;
    game.sweep_gemstack_right();
    while (!game.gemstack_is_at_floor())
        game.advance_gemstack();
    game.add_current_gemstack_to_blob();
    game.update_floor();
    game.update_gemstack();
    while (!game.gemstack_is_at_floor())
        game.advance_gemstack();
    game.sweep_gemstack_right();
    BOOST_CHECK_EQUAL(game.get_current_gemstack()->get_first_x(),
                        settings::board_width-1);
}

BOOST_AUTO_TEST_CASE(SweepLeftBlockedTest)
{
    Game game;
    game.sweep_gemstack_left();
    while (!game.gemstack_is_at_floor())
        game.advance_gemstack();
    game.add_current_gemstack_to_blob();
    game.update_floor();
    game.update_gemstack();
    while (!game.gemstack_is_at_floor())
        game.advance_gemstack();
    BOOST_CHECK_EQUAL(game.__measure_distance_to_left_blocking_gem(),
                      settings::board_middle-1);
    game.sweep_gemstack_left();
    BOOST_CHECK_EQUAL(game.get_current_gemstack()->get_first_x(), 1);
}

BOOST_AUTO_TEST_CASE(ToggleOrientationBlockedTest)
{
    Game game;
    game.sweep_gemstack_right();
    game.shift_gemstack_left();
    BOOST_CHECK_EQUAL( game.get_current_gemstack()->get_first_x(),
                       settings::board_width-1);
    while (!game.gemstack_is_at_floor())
        game.advance_gemstack();
    BOOST_CHECK_EQUAL( game.get_current_gemstack()->get_first_y(),
                       settings::board_height);

    game.add_current_gemstack_to_blob();
    game.update_floor();
    BOOST_CHECK_EQUAL( game.get_floor()[settings::board_width - 1],
                       settings::board_height - settings::gems_in_gemstack);
    game.update_gemstack();
    game.sweep_gemstack_right();
    BOOST_CHECK_EQUAL( game.get_current_gemstack()->get_first_x(),
                       settings::board_width);
    while (!game.gemstack_is_at_floor())
        game.advance_gemstack();
    game.toggle_gemstack_orientation();
    BOOST_CHECK_EQUAL(game.get_gemstack_orientation(),
                      DOWN);
    game.toggle_gemstack_orientation();
    BOOST_CHECK_EQUAL(game.get_gemstack_orientation(),
                      UP);
}

BOOST_AUTO_TEST_CASE(GetFloorTest)
{
    Game game;
    floor_t floor;
    std::fill(floor.begin(), floor.end(), settings::board_height);
    floor_t game_floor = game.get_floor();
    BOOST_CHECK_EQUAL_COLLECTIONS(floor.begin(), floor.end(),
                                  game_floor.begin(), game_floor.end());
}

BOOST_AUTO_TEST_CASE(ConnectorCountBlobTest)
{
    Game game;
    for (int i = 0; i < settings::gems_to_connect - 1; i++)
        game.add_gem_to_blob(std::make_unique<Gem>
                         (RED_C, settings::board_width, settings::board_height - i));
    BOOST_CHECK_EQUAL(game.get_blob()->operator[](0).size(), settings::gems_to_connect - 1);
    BOOST_CHECK_EQUAL(game.get_blob()->size(), 1);
    game.destroy_blob_connectors();
    BOOST_CHECK_EQUAL(game.get_blob()->size(), 1);
    game.add_gem_to_blob(std::make_unique<Gem>
                         (RED_C, settings::board_width, settings::board_height - settings::gems_to_connect + 1));
    BOOST_CHECK_EQUAL(game.get_blob()->operator[](0).size(), settings::gems_to_connect);
    game.destroy_blob_connectors();
    BOOST_CHECK_EQUAL(game.get_blob()->size(), 0);
}

BOOST_AUTO_TEST_CASE(BlobInitialSizeTest)
{
    Game game;
    BOOST_CHECK_EQUAL(game.count_gems_in_blob(), 0);
}

BOOST_AUTO_TEST_CASE(InitialPointsTest)
{
    Game game;
    BOOST_CHECK_EQUAL( game.get_current_score(), 0 );
    BOOST_CHECK( settings::points_per_gemstack > 0 );
    BOOST_CHECK( settings::points_per_additional_gem > 0 );
}

BOOST_AUTO_TEST_CASE(AddPointsTest)
{
    Game game;
    for (int i = 0; i < settings::gems_to_connect; i++)
        game.add_gem_to_blob(std::make_unique<Gem>
                         (RED_C, settings::board_width, settings::board_height - i));
    game.add_gem_to_blob(std::make_unique<Gem>
                         (YELLOW_C, settings::board_width, settings::board_height -
                          settings::gems_to_connect));
    BOOST_CHECK_EQUAL( game.get_blob()->operator[](0).size(), settings::gems_to_connect);
    BOOST_CHECK( game.get_blob()->operator[](0).size() - settings::gems_to_connect == 0 );
    blob_t destroyed_gems = game.destroy_blob_connectors();
    BOOST_CHECK_EQUAL( destroyed_gems[0].size(), settings::gems_to_connect );
    game.add_points( destroyed_gems );
    BOOST_CHECK_EQUAL( game.get_current_score(), settings::points_per_gemstack );
    BOOST_CHECK( game.get_current_score() > 0 );
}

BOOST_AUTO_TEST_CASE(OrientationOutOfBoundsTest)
{
    Game game;
    game.sweep_gemstack_left();
    game.set_gemstack_orientation(LEFT);
    BOOST_CHECK_EQUAL(game.get_current_gemstack()->get_first_x(), 0);
}

#endif // TEST




