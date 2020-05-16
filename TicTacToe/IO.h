#pragma once
#include <iostream>
#include <Windows.h>
#include <string>

#include "constants.h"

using namespace std;

void init();

void set_cursor_position(COORD c);
void set_cursor_color(int color);

void fill_grid_positions();
void print_grid();

void print_sign(COORD t, Signs sign);
void repaint_field();
void print_info();

string convert_turn_to_string(Turns t);
char convert_sign_to_char(Signs sign);
string convert_difficulty_to_string(Difficulties diff);

bool convert_char_to_bool(char c);
bool compare_str(string s1, string s2);
bool compare_str(string s1, char s2);
