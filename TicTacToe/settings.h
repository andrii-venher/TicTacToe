#pragma once
#include <iostream>
#include <Windows.h>
#include <string>
#include <ctime>

#include "constants.h"

using namespace std;

Signs field[FIELD_SIZE][FIELD_SIZE];

COORD GRID_POSITIONS[FIELD_SIZE][FIELD_SIZE];

Signs player_value = Signs::X_SIGN;
Signs comp_value = Signs::O_SIGN;
Signs empty_value = Signs::EMPTY_SIGN;

Difficulties difficulty = Difficulties::EASY;

Turns whos_first_turn = Turns::PLAYER_TURN;

int player_points = 0;
int comp_points = 0;

int hints = 3;

bool isMatch = false;

//menu settings

const short MENU_TEXT_SHIFT = 2;

const string GAME_MENU_TEXT[] = { "START", "OPTIONS", "GET A HINT", "ABOUT GAME"};
const int GAME_MENU_ELEMENTS_AMOUNT = sizeof(GAME_MENU_TEXT) / sizeof(string);
COORD GAME_MENU_POSITION[GAME_MENU_ELEMENTS_AMOUNT];
const int ACTIVE_GAME_MENU_ELEMENTS_INDEXES[] = { 0, 1, 2, 3 };
const int ACTIVE_GAME_MENU_ELEMENTS_AMOUNT = sizeof(ACTIVE_GAME_MENU_ELEMENTS_INDEXES) / sizeof(int);
