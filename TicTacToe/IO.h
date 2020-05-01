#pragma once
#include <iostream>
#include <Windows.h>
#include <string>
#include <ctime>

#include "settings.h"

using namespace std;

void init();

void set_cursor_position(COORD c);
void set_cursor_color(int color);

void fill_grid_positions();
void print_grid();

void print_sign(COORD t, signs sign);
void repaint_field();
void print_info();

string convert_turn_to_string(turns t);
char convert_sign_to_char(signs sign);
string convert_difficulty_to_string(difficulties diff);

//sets initial screen settings, hides cursor and sets random number function
void init()
{
	system("title Tic-Tac-Toe");
	MoveWindow(GetConsoleWindow(), 0, 0, 0, 0, true);
	system(("mode con cols=" + to_string(FIELD_WIDTH + 1) + " lines=" + to_string(FIELD_HEIGHT + 6)).c_str());

	CONSOLE_CURSOR_INFO cci;
	cci.bVisible = false;
	cci.dwSize = 100;
	SetConsoleCursorInfo(handle, &cci);

	srand(time(0));
	rand();
}

//puts cursor on passed coordinates
void set_cursor_position(COORD c)
{
	SetConsoleCursorPosition(handle, c);
}

//sets cursor color
void set_cursor_color(int color)
{
	SetConsoleTextAttribute(handle, color);
}

//gives coordinates to places of field
void fill_grid_positions()
{
	for (int i = 0; i < FIELD_SIZE; i++)
	{
		for (int j = 0; j < FIELD_SIZE; j++)
		{
			GRID_POSITIONS[i][j] = { short(j * IMAGE_WIDTH + j + 1), short(i * IMAGE_HEIGHT + i + 2) };
		}
	}
}

//prints outlines of field
void print_grid()
{
	//because grid contains FIELD_SIZE+1 walls and FIELD_SIZE empty_images
	set_cursor_position({ 0, 1 });
	for (int i = 0; i < FIELD_HEIGHT; i++)
	{
		for (int j = 0; j < FIELD_WIDTH; j++)
		{
			if (i % (IMAGE_HEIGHT + 1) == 0)
			{
				set_cursor_color(FULL_WHITE);
				cout << " ";
			}
			else if (j % (IMAGE_WIDTH + 1) == 0)
			{
				set_cursor_color(FULL_WHITE);
				cout << " ";
			}
			else {
				set_cursor_color(WHITE);
				cout << " ";
			}
			
		}
		cout << endl;
	}
	set_cursor_color(WHITE);
}

//prints passed sign on a field
void print_sign(COORD t, signs sign)
{
	if (sign == signs::X_SIGN)
	{
		set_cursor_color(RED);
		for (int i = 0; i < IMAGE_HEIGHT; i++)
		{
			set_cursor_position(t);
			cout << X_IMAGE[i];
			t.Y++;
		}
	}
	else if (sign == signs::O_SIGN)
	{
		set_cursor_color(BLUE);
		for (int i = 0; i < IMAGE_HEIGHT; i++)
		{
			set_cursor_position(t);
			cout << O_IMAGE[i];
			t.Y++;
		}
	}
	else if (sign == signs::HINT)
	{
		set_cursor_color(FULL_YELLOW);
		for (int i = 0; i < IMAGE_HEIGHT; i++)
		{
			set_cursor_position(t);
			cout << EMPTY_IMAGE[i];
			t.Y++;
		}
	}
	else if (sign == signs::EMPTY_SIGN)
	{
		set_cursor_color(WHITE);
		for (int i = 0; i < IMAGE_HEIGHT; i++)
		{
			set_cursor_position(t);
			cout << EMPTY_IMAGE[i];
			t.Y++;
		}
	}
	set_cursor_color(WHITE);
}

//repaints field after change
void repaint_field()
{
	for (int i = 0; i < FIELD_SIZE; i++)
	{
		for (int j = 0; j < FIELD_SIZE; j++)
		{
			if (field[i][j] == player_value) {
				print_sign(GRID_POSITIONS[i][j], player_value);
			}
			else if (field[i][j] == comp_value) {
				print_sign(GRID_POSITIONS[i][j], comp_value);
			}
		}
	}
}

//repaints info bar after change
void print_info()
{
	COORD t = { 0, FIELD_HEIGHT + 1 };
	set_cursor_color(WHITE);
	set_cursor_position(t);
	cout << "Difficulty: " << convert_difficulty_to_string(difficulty);
	t.Y++;
	set_cursor_position(t);
	cout << "Who's first turn: " << convert_turn_to_string(whos_first_turn);
	t.Y++;
	set_cursor_position(t);
	cout << "Your sign: " << convert_sign_to_char(player_value);
	t.Y++;
	set_cursor_position(t);
	cout << "Hints left: " << hints;
	t.Y++;
	set_cursor_position(t);
	cout << "PLAYER " << player_points << " : " << comp_points << " COMPUTER";
}

//converts whos first turn to string
string convert_turn_to_string(turns t)
{
	switch (t)
	{
	case PLAYER_TURN:
		return "PLAYER";
	case COMP_TURN:
		return "COMPUTER";
	default:
		break;
	}
}

//converts sign to a char
char convert_sign_to_char(signs sign)
{
	switch (sign)
	{
	case O_SIGN:
		return 'O';
	case X_SIGN:
		return 'X';
	default:
		break;
	}
}

//converts difficulty to a string
string convert_difficulty_to_string(difficulties difficulty)
{
	switch (difficulty)
	{
	case EASY:
		return "EASY";
	case MID:
		return "MID";
	case HARD:
		return "HARD";
	default:
		break;
	}
}







