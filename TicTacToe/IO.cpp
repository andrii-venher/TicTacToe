#include <iostream>
#include <Windows.h>
#include <string>
#include <ctime>

#include "IO.h"
#include "Settings.h"
#include "Constants.h"


//sets initial screen settings, hides cursor and sets random number function
void init()
{
	system("title Tic-Tac-Toe");
	MoveWindow(GetConsoleWindow(), 0, 0, 0, 0, true);
	system(("mode con cols=" + to_string(FIELD_WIDTH + 1) + " lines=" + to_string(FIELD_HEIGHT + 7)).c_str());

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
			grid_pos[i][j] = { short(j * IMAGE_WIDTH + j + 1), short(i * IMAGE_HEIGHT + i + 3) };
		}
	}
}

//prints outlines of field
void print_grid()
{
	//because grid contains FIELD_SIZE+1 walls and FIELD_SIZE empty_images
	set_cursor_position({ 0, 2 });
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
void print_sign(COORD t, Signs sign)
{
	if (sign == Signs::X_SIGN)
	{
		set_cursor_color(RED);
		for (int i = 0; i < IMAGE_HEIGHT; i++)
		{
			set_cursor_position(t);
			cout << X_IMAGE[i];
			t.Y++;
		}
	}
	else if (sign == Signs::O_SIGN)
	{
		set_cursor_color(BLUE);
		for (int i = 0; i < IMAGE_HEIGHT; i++)
		{
			set_cursor_position(t);
			cout << O_IMAGE[i];
			t.Y++;
		}
	}
	else if (sign == Signs::HINT)
	{
		set_cursor_color(FULL_YELLOW);
		for (int i = 0; i < IMAGE_HEIGHT; i++)
		{
			set_cursor_position(t);
			cout << EMPTY_IMAGE[i];
			t.Y++;
		}
	}
	else if (sign == Signs::EMPTY_SIGN)
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
				print_sign(grid_pos[i][j], player_value);
			}
			else if (field[i][j] == computer_value) {
				print_sign(grid_pos[i][j], computer_value);
			}
		}
	}
}

//repaints info bar after change
void print_info()
{
	COORD t = { 0, FIELD_HEIGHT + 2 };
	set_cursor_color(WHITE);
	set_cursor_position(t);
	cout << "DIFFICULTY: " << convert_difficulty_to_string(difficulty);
	t.Y++;
	set_cursor_position(t);
	cout << "WHOSE FIRST TURN: " << convert_turn_to_string(whose_first_turn);
	t.Y++;
	set_cursor_position(t);
	cout << "YOUR SIGN: " << convert_sign_to_char(player_value);
	t.Y++;
	set_cursor_position(t);
	cout << "HINTS LEFT: " << hints;
	t.Y++;
	set_cursor_position(t);
	cout << "PLAYER " << player_points << " : " << computer_points << " COMPUTER";
}

//converts whos first turn to string
string convert_turn_to_string(Turns t)
{
	switch (t)
	{
	case PLAYER_TURN:
		return "PLAYER\n";
	case COMP_TURN:
		return "COMPUTER\n";
	default:
		break;
	}
}

//converts sign to a char
char convert_sign_to_char(Signs sign)
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
string convert_difficulty_to_string(Difficulties difficulty)
{
	switch (difficulty)
	{
	case EASY:
		return "EASY\n";
	case MID:
		return "MID\n";
	case HARD:
		return "HARD\n";
	default:
		break;
	}
}

bool convert_char_to_bool(char c)
{
	if (c == 't')
		return true;
	else if (c == 'f')
		return false;
}

bool compare_str(string s1, string s2)
{
	for (int i = 0; i < s1.length(); i++)
	{
		if (s1[i] == '\n')
			s1[i] = '\0';
		s1[i] = tolower(s1[i]);
	}
	for (int i = 0; i < s2.length(); i++)
	{
		if (s2[i] == '\n')
			s2[i] = '\0';
		s2[i] = tolower(s2[i]);
	}
	if (s1 == s2)
		return true;
	else
		return false;
}

bool compare_str(string s1, char s2)
{
	string t;
	t.push_back(s2);
	t.push_back('\n');
	return compare_str(s1, t);
}
