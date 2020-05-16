#include <iostream>
#include <Windows.h>
#include <string>
#include <ctime>

#include "settings.h"
#include "constants.h"

using namespace std;

Signs field[FIELD_SIZE][FIELD_SIZE];

COORD grid_pos[FIELD_SIZE][FIELD_SIZE];

Signs player_value = Signs::X_SIGN;
Signs computer_value = Signs::O_SIGN;
Signs empty_value = Signs::EMPTY_SIGN;

Difficulties difficulty = Difficulties::EASY;

Turns whos_first_turn = Turns::PLAYER_TURN;

int player_points = 0;
int computer_points = 0;

int hints = 3;

bool is_match = false;