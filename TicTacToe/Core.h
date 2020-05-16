#pragma once
#include <iostream>
#include <Windows.h>

#include "MyMenu.h"

using namespace std;

void clear_field();

void computer_move();
COORD random_choice();
COORD best_choice(Turns t, Signs sign);
int minimax(int depth, bool is_comp_turn);

void game_mouse_track(MenuBar mb);
void get_hint();

int get_state();

void gameover(int state);

COORD convert_indexes_to_coordinates(COORD move);
States convert_to_state(Signs sign);

void game();
void play_match(MenuBar mb);
