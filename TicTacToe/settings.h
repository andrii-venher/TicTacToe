#pragma once
#include <iostream>
#include <Windows.h>
#include <string>
#include <ctime>

#include "constants.h"

using namespace std;

signs field[FIELD_SIZE][FIELD_SIZE];

COORD GRID_POSITIONS[FIELD_SIZE][FIELD_SIZE];

signs player_value = signs::X_SIGN;
signs comp_value = signs::O_SIGN;
signs empty_value = signs::EMPTY_SIGN;

difficulties difficulty = difficulties::EASY;

turns whos_first_turn = turns::PLAYER_TURN;

int player_points = 0;
int comp_points = 0;

int hints = 3;

bool isMatch = false;

//menu settings

const short MENU_TEXT_SHIFT = 2;

const string OPTIONS_MENU_TEXT[] = { "OPTIONS", "DIFFICULTY:", "EASY", "MID", "HARD", "WHOS TURN:", "PLAYER", "COMPUTER", "CHOOSE YOUR SIGN:", "X", "O", "SAVE" };
const int OPTIONS_MENU_ELEMENTS_AMOUNT = sizeof(OPTIONS_MENU_TEXT) / sizeof(string);
COORD OPTIONS_MENU_POSITION[OPTIONS_MENU_ELEMENTS_AMOUNT];
const int ACTIVE_OPTIONS_MENU_ELEMENTS_INDEXES[] = { 2, 3, 4, 6, 7, 9, 10, 11 };
const int ACTIVE_OPTIONS_MENU_ELEMENTS_AMOUNT = sizeof(ACTIVE_OPTIONS_MENU_ELEMENTS_INDEXES) / sizeof(int);

const string GAME_MENU_TEXT[] = { "START", "OPTIONS", "GET A HINT", "ABOUT GAME"};
const int GAME_MENU_ELEMENTS_AMOUNT = sizeof(GAME_MENU_TEXT) / sizeof(string);
COORD GAME_MENU_POSITION[GAME_MENU_ELEMENTS_AMOUNT];
const int ACTIVE_GAME_MENU_ELEMENTS_INDEXES[] = { 0, 1, 2, 3 };
const int ACTIVE_GAME_MENU_ELEMENTS_AMOUNT = sizeof(ACTIVE_GAME_MENU_ELEMENTS_INDEXES) / sizeof(int);

const string TITRES_MENU_TEXT[] = { "Created by Venger Andrey", "BACK"};
const int TITRES_MENU_ELEMENTS_AMOUNT = sizeof(TITRES_MENU_TEXT) / sizeof(string);
COORD TITRES_MENU_POSITION[TITRES_MENU_ELEMENTS_AMOUNT];
const int ACTIVE_TITRES_MENU_ELEMENTS_INDEXES[] = { 1 };
const int ACTIVE_TITRES_MENU_ELEMENTS_AMOUNT = sizeof(ACTIVE_TITRES_MENU_ELEMENTS_INDEXES) / sizeof(int);