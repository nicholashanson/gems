#define TEST
#define BOOST_TEST_MODULE TestSuite
#include <boost/test/included/unit_test.hpp>
#include "Game.h"
#include <algorithm>
#ifndef TEST
int main(){}
#endif

#ifdef TEST
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

BOOST_AUTO_TEST_CASE(RotateGemTest)
{
    Game game;
    color_t first_before = game.get_current_gemstack()->get_first_gem()->get_color();
    game.rotate_gemstack();
    color_t last_after = game.get_current_gemstack()->get_last_gem()->get_color();
    BOOST_CHECK_EQUAL(first_before, last_after);
}

BOOST_AUTO_TEST_CASE(GemInitialOrientationTest)
{
    Game game;
    BOOST_CHECK_EQUAL(game.get_gemstack_orientation(), UP);
}

BOOST_AUTO_TEST_CASE(OrientationShuffleTest)
{
    Game game;
    game.toggle_orientation();
    BOOST_CHECK_EQUAL(game.get_gemstack_orientation(), RIGHT);
    game.toggle_orientation();
    BOOST_CHECK_EQUAL(game.get_gemstack_orientation(), DOWN);
    game.toggle_orientation();
    BOOST_CHECK_EQUAL(game.get_gemstack_orientation(), LEFT);
    game.toggle_orientation();
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

BOOST_AUTO_TEST_CASE(RedGemCountTest)
{
    Game game;
    game.generate_test_blob();
    BOOST_CHECK_EQUAL(game.get_red_gem_count(), 3);
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
    game.add_gem_to_blob(std::make_unique<Gem>
                         (RED, settings::board_width, settings::board_height));
    BOOST_CHECK_EQUAL(game.get_blob()->operator[](0).size(), 1);
    game.add_gem_to_blob(std::make_unique<Gem>
                         (RED, settings::board_width, settings::board_height-1));
    BOOST_CHECK_EQUAL(game.get_blob()->operator[](0).size(), 2);
    game.add_gem_to_blob(std::make_unique<Gem>
                         (RED, settings::board_width, settings::board_height-2));
    BOOST_CHECK_EQUAL(game.get_blob()->operator[](0).size(), 3);
    BOOST_CHECK_EQUAL(game.get_blob()->size(), 1);
    game.destroy_blob_connectors();
    BOOST_CHECK_EQUAL(game.get_blob()->size(), 1);
    BOOST_CHECK_EQUAL(game.get_blob()->operator[](0).size(), 3);
    game.add_gem_to_blob(std::make_unique<Gem>
                         (RED, settings::board_width, settings::board_height-3));
    BOOST_CHECK_EQUAL(game.get_blob()->operator[](0).size(), 4);
    game.destroy_blob_connectors();
    BOOST_CHECK_EQUAL(game.get_blob()->size(), 0);
}

BOOST_AUTO_TEST_CASE(BlobInitialSizeTest)
{
    Game game;
    BOOST_CHECK_EQUAL(game.get_blob_size(), 0);
}
/*


BOOST_AUTO_TEST_CASE(SetCurrentGemStackTest)
{
    Game game;
    game.set_current_gemstack(BLUE,BLUE,BLUE);
    BOOST_CHECK_EQUAL(game.get_current_gemstack_colors(), std::make_tuple(BLUE, BLUE, BLUE));
}


BOOST_AUTO_TEST_CASE(ConnectedGroupsDestroyedTest)
{
    Game game;
    game.set_current_gemstack(BLUE,BLUE,BLUE);

    for (int i = 0, i < settings::number_to_connect - 1; i++)
    {
        game.set_next(RED, BLUE, GREEN);
        game.shift_right(i);
        game.drop_gem();
        BOOST_CHECK_EQUAL(game.number_of_connected_groups(), 0);
    }
    game.set_next(RED, BLUE, GREEN);
    game.shift_right(SETTINGS::number_to_connect - 1);
    game.drop_gem();
    BOOST_CHECK_EQUAL(game.number_of_connected_groups(), 3);
}



BOOST_AUTO_TEST_CASE(BlobGrowthTest)
{
    Game game;
    game.set_next(RED, BLUE, GREEN);
    game.drop_gem();
    BOOST_CHECK_EQUAL(game.blob_size(), 3);
}

BOOST_AUTO_TEST_CASE(DestroyAllTest)
{
    Game game;
    game.generate_random_blob();
    game.destroy_all(BLUE);
    BOOST_CHECK(!game.blob_contains(BLUE));
}

BOOST_AUTO_TEST_CASE(NumberDestroyedTest)
{
    Game game;
    game.generate_blob();
    auto blob_size = game.blob_size();
    game.destroy();
    BOOST_CHECK_EQUAL(blob_size, game.blob_size() + game.number_gems_destroyed());
}

BOOST_AUTO_TEST_CASE(ClearAllTest)
{
    Game game;
    game.generate_blob();
    game.clear_all();
    BOOST_CHECK_EQUAL(game.blob_size(), 0);
}

BOOST_AUTO_TEST_CASE(SimpleCascadeTest)
{
    Game game;
    game.cascade({1, 2, 4, 5});
    BOOST_CHECK_EQUAL(game.cascade_result(), {1, 2, 3, 4});
}

BOOST_AUTO_TEST_CASE(PairCascadeTest)
{
    Game game;
    game.cascade({(1,1), (2,1), (4, 1), (5,1)});
    BOOST_CHECK_EQUAL(game.cascade_result(), {(1,1), (2,1), (3,1), (4,1)});
}
*/
#endif
