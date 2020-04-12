#include <iostream>
#include <Windows.h>
#include <string>
#include <ctime>
#include <limits>

using namespace std;

HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

COORD c;
COORD grid = { 1, 4 };
COORD info = { 1, 0 };

const int field_size = 3;

const int cols = 39;
const int lines = 30;
short w = (cols - 2 - 4) / field_size;
short h = (lines - 1 - grid.Y) / field_size;

const int empty_sign = -1;
const int x_sign = 1;
const int o_sign = 0;
const int draw_value = 666;
const int no_winner = 88;

const bool ai_turn = true;
const bool player_turn = false;

string player_symbol[7] = { "  *     *  " ,
							"   *   *   " ,
							"    * *    " ,
							"     *     " ,
							"    * *    " ,
							"   *   *   " ,
							"  *     *  " };
string comp_symbol[7] = { "  *******  " ,
							" *       * " ,
							" *       * " ,
							" *       * " ,
							" *       * " ,
							" *       * " ,
							"  *******  " };

enum colors { FULL_WHITE = 255, WHITE = 7, RED = 12, BLUE = 9, GREEN = 10, YELLOW = 14 };
enum scores { PLAYER = -100, COMP = 100, DRAW = 0 };
