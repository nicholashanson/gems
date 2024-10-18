#include "Game.h"

Game::Game()
{
    this->generate_gemstack();
}

Game::~Game()
{
    delete this->get_current_gemstack();
}

GemStack* Game::get_current_gemstack()
{
    return current_gemstack;
}

void Game::rotate_gemstack()
{
    this->get_current_gemstack()->rotate_gemstack();
}

void Game::generate_gemstack()
{
    this->current_gemstack = new GemStack(RED,BLUE,GREEN);
}

void Game::toggle_orientation()
{
    this->get_current_gemstack()->toggle_orientation();
}

xy_t Game::get_first_xy()
{
    return this->get_current_gemstack()->get_first_xy();
}

int Game::get_first_x()
{
    return this->get_current_gemstack()->get_first_x();
}

int Game::get_first_y()
{
    return this->get_current_gemstack()->get_first_y();
}

int Game::get_middle_x()
{
    return this->get_current_gemstack()->get_middle_x();
}

int Game::get_middle_y()
{
    return this->get_current_gemstack()->get_middle_y();
}

int Game::get_last_x()
{
    return this->get_current_gemstack()->get_last_x();
}

int Game::get_last_y()
{
    return this->get_current_gemstack()->get_last_y();
}

void Game::advance_gemstack()
{
    this->get_current_gemstack()->advance_gemstack();
}

void Game::shift_gemstack_right()
{
    this->get_current_gemstack()->shift_right();
}

void Game::shift_gemstack_left()
{
    this->get_current_gemstack()->shift_left();
}

orientation_t Game::get_gemstack_orientation()
{
    return this->get_current_gemstack()->get_current_orientation();
}

void Game::set_gemstack_orientation(const orientation_t ori)
{
    this->get_current_gemstack()->set_orientation(ori);
}

void Game::sweep_gemstack_right()
{
    this->get_current_gemstack()->sweep_right();
}

void Game::sweep_gemstack_left()
{
    this->get_current_gemstack()->sweep_left();
}

gemstack_t Game::get_current_gemstack_colors()
{
    return this->get_current_gemstack()->get_gem_colors();
}

floor_t Game::get_floor()
{
    return this->blob.get_floor();
}

void Game::generate_test_blob()
{
    gem_uptr gem_0 = std::make_unique<Gem>(RED, settings::board_width, settings::board_height);
    gem_uptr gem_1 = std::make_unique<Gem>(RED, settings::board_width, settings::board_height - 1);
    //Gem gem_2(GREEN, settings::board_width, settings::board_height - 2);
    //Gem gem_3(RED, settings::board_width - 1, settings::board_height);
    //Gem gem_4(GREEN, settings::board_width - 1, settings::board_height - 1);
    //Gem gem_5(BLUE, settings::board_width - 1, settings::board_height - 2);
    //Gem gem_6(RED, settings::board_width - 2, settings::board_height);
    //Gem gem_7(YELLOW, settings::board_width - 2, settings::board_height - 1);
    //Gem gem_8(YELLOW, settings::board_width - 2, settings::board_height - 2);
    this->blob.add_gem_to_blob(std::move(gem_0));
    this->blob.add_gem_to_blob(std::move(gem_1));
    //this->blob.add_to_blob(gem_2);
    //this->blob.add_to_blob(gem_3);
    //this->blob.add_to_blob(gem_4);
    //this->blob.add_to_blob(gem_5);
    //this->blob.add_to_blob(gem_6);
    //this->blob.add_to_blob(gem_7);
    //this->blob.add_to_blob(gem_8);
}

int Game::get_red_gem_count()
{
    return this->blob.get_red_gem_count();
}

int Game::get_connector_count()
{
    return this->blob.get_connector_count();
}

auto Game::get_blob(void) -> blob_t*
{
    return this->blob.get_blob();
}

void Game::add_gem_to_blob(gem_uptr gem)
{
    return this->blob.add_gem_to_blob( std::move(gem) );
}

blob_t Game::destroy_blob_connectors()
{
    return this->blob.destroy_connectors();
}

auto Game::get_blob_size() -> count_t
{
    return blob.get_blob_size();
}

