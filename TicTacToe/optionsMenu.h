#pragma once
#include <iostream>
#include <Windows.h>
#include <string>
#include <ctime>

#include "settings.h"
#include "constants.h"
#include "IO.h"

using namespace std;

void call_options_menu();
void fill_options_menu_position(COORD pos[]);
void start_options_mouse_track();
void print_options_menu();

//fills options menu elements` positions, prints options menu and starts tracking of mouse in options menu
void call_options_menu()
{
	fill_options_menu_position(OPTIONS_MENU_POSITION);
	print_options_menu();
	start_options_mouse_track();
}

//gives positions on screen to elements of options menu
void fill_options_menu_position(COORD pos[]) {
	short next_row_Y = 0;
	for (short i = 0; i < OPTIONS_MENU_ELEMENTS_AMOUNT; i++)
	{
		if (i == 0)
		{
			pos[i] = { short(FIELD_WIDTH - OPTIONS_MENU_TEXT[0].length()) / 2, 0 };
		}
		else if (i == 1)
		{
			pos[i] = { 0, ++next_row_Y };
		}
		else if (i <= 4)
		{
			pos[i] = { pos[i - 1].X + short(OPTIONS_MENU_TEXT[i - 1].length() + MENU_TEXT_SHIFT), pos[i - 1].Y };
		}
		else if (i == 5)
		{
			pos[i] = { 0, ++next_row_Y };
		}
		else if (i <= 7)
		{
			pos[i] = { pos[i - 1].X + short(OPTIONS_MENU_TEXT[i - 1].length() + MENU_TEXT_SHIFT), pos[i - 1].Y };
		}
		else if (i == 8)
		{
			pos[i] = { 0, ++next_row_Y };
		}
		else if (i <= 10)
		{
			pos[i] = { pos[i - 1].X + short(OPTIONS_MENU_TEXT[i - 1].length() + MENU_TEXT_SHIFT), pos[i - 1].Y };
		}
		else
		{
			pos[i] = { short(FIELD_WIDTH - OPTIONS_MENU_TEXT[0].length()) / 2, next_row_Y += 2 };
		}
	}
}

//prints options menu on screen
void print_options_menu()
{
	system("cls");
	set_cursor_color(WHITE);
	for (int i = 0; i < OPTIONS_MENU_ELEMENTS_AMOUNT; i++)
	{
		set_cursor_position(OPTIONS_MENU_POSITION[i]);
		cout << OPTIONS_MENU_TEXT[i];
	}
}

//tracks mouse actions in options menu
void start_options_mouse_track()
{
	HANDLE handle_in = GetStdHandle(STD_INPUT_HANDLE);
	SetConsoleMode(handle_in, ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
	const int events_count = 256;
	INPUT_RECORD all_events[events_count];
	DWORD read_event;

	COORD c;

	int last_index = ACTIVE_OPTIONS_MENU_ELEMENTS_INDEXES[0];

	while (true)
	{
		ReadConsoleInput(handle_in, all_events, events_count, &read_event);
		for (int i = 0; i < read_event; i++)
		{
			c.X = all_events[i].Event.MouseEvent.dwMousePosition.X;
			c.Y = all_events[i].Event.MouseEvent.dwMousePosition.Y;

			if (all_events[i].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
			{
				for (int j = 0; j < OPTIONS_MENU_ELEMENTS_AMOUNT; j++)
				{
					if (c.Y == OPTIONS_MENU_POSITION[j].Y && c.X >= OPTIONS_MENU_POSITION[j].X && c.X < OPTIONS_MENU_POSITION[j].X + OPTIONS_MENU_TEXT[j].length())
					{
						for (int u = 0; u < ACTIVE_OPTIONS_MENU_ELEMENTS_AMOUNT; u++)
						{
							if (j == ACTIVE_OPTIONS_MENU_ELEMENTS_INDEXES[u]) {
								//if save button is pressed (which is last in menu)
								if (j == ACTIVE_OPTIONS_MENU_ELEMENTS_INDEXES[ACTIVE_OPTIONS_MENU_ELEMENTS_AMOUNT - 1])
								{
									return;
								}
								else if (j == ACTIVE_OPTIONS_MENU_ELEMENTS_INDEXES[0])
								{
									difficulty = difficulties::EASY;
								}
								else if (j == ACTIVE_OPTIONS_MENU_ELEMENTS_INDEXES[1])
								{
									difficulty = difficulties::MID;
								}
								else if (j == ACTIVE_OPTIONS_MENU_ELEMENTS_INDEXES[2])
								{
									difficulty = difficulties::HARD;
								}
								else if (j == ACTIVE_OPTIONS_MENU_ELEMENTS_INDEXES[3])
								{
									whos_first_turn = turns::PLAYER_TURN;
								}
								else if (j == ACTIVE_OPTIONS_MENU_ELEMENTS_INDEXES[4])
								{
									whos_first_turn = turns::COMP_TURN;
								}
								else if (j == ACTIVE_OPTIONS_MENU_ELEMENTS_INDEXES[5])
								{
									player_value = signs::X_SIGN;
									comp_value = signs::O_SIGN;
								}
								else if (j == ACTIVE_OPTIONS_MENU_ELEMENTS_INDEXES[6])
								{
									player_value = signs::O_SIGN;
									comp_value = signs::X_SIGN;
								}
								set_cursor_color(GREEN);
								set_cursor_position(OPTIONS_MENU_POSITION[j]);
								cout << OPTIONS_MENU_TEXT[j];
								if (last_index != j)
								{
									set_cursor_color(WHITE);
									set_cursor_position(OPTIONS_MENU_POSITION[last_index]);
									cout << OPTIONS_MENU_TEXT[last_index];
									last_index = j;
								}
							}
						}
					}
				}
			}
		}
	}
}