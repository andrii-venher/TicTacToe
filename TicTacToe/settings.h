#pragma once
#include <iostream>
#include <Windows.h>
#include <string>
#include <ctime>

#include "constants.h"

using namespace std;

extern Signs field[FIELD_SIZE][FIELD_SIZE];

extern COORD grid_pos[FIELD_SIZE][FIELD_SIZE];

extern Signs player_value;
extern Signs computer_value;
extern Signs empty_value;

extern Difficulties difficulty;

extern Turns whos_first_turn;

extern int player_points;
extern int computer_points;

extern int hints;

extern bool is_match;

