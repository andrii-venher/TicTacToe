#pragma once
#include <iostream>
#include <Windows.h>
#include <string>
#include <ctime>

#include "settings.h"
#include "constants.h"
#include "IO.h"

using namespace std;

void call_titres_menu();
void print_titres_menu();
void fill_titres_menu_position(COORD pos[]);
void start_titres_mouse_track();

//fills titres menu elements` positions, prints titres menu and starts tracking of mouse in titres menu
void call_titres_menu()
{
	fill_titres_menu_position(TITRES_MENU_POSITION);
	print_titres_menu();
	start_titres_mouse_track();
}

//gives positions on screen to elements of titres menu
void fill_titres_menu_position(COORD pos[]) 
{
	pos[0] = { 0, 0 };
	for (short i = 1; i < TITRES_MENU_ELEMENTS_AMOUNT; i++)
	{
		if (i == TITRES_MENU_ELEMENTS_AMOUNT - 1)
		{
			pos[i] = { FIELD_WIDTH/2, pos[i - 1].Y + 2 };
		}
	}
}

//prints titres menu on screen
void print_titres_menu()
{
	system("cls");
	set_cursor_color(WHITE);
	for (int i = 0; i < TITRES_MENU_ELEMENTS_AMOUNT; i++)
	{
		set_cursor_position(TITRES_MENU_POSITION[i]);
		cout << TITRES_MENU_TEXT[i];
	}
}

//tracks mouse actions in titres menu
void start_titres_mouse_track()
{
	HANDLE handle_in = GetStdHandle(STD_INPUT_HANDLE);
	SetConsoleMode(handle_in, ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
	const int events_count = 256;
	INPUT_RECORD all_events[events_count];
	DWORD read_event;

	COORD c;

	while (true)
	{
		ReadConsoleInput(handle_in, all_events, events_count, &read_event);
		for (int i = 0; i < read_event; i++)
		{
			c.X = all_events[i].Event.MouseEvent.dwMousePosition.X;
			c.Y = all_events[i].Event.MouseEvent.dwMousePosition.Y;

			if (all_events[i].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
			{
				for (int j = 0; j < TITRES_MENU_ELEMENTS_AMOUNT; j++)
				{
					if (c.Y == TITRES_MENU_POSITION[j].Y && c.X >= TITRES_MENU_POSITION[j].X && c.X < TITRES_MENU_POSITION[j].X + TITRES_MENU_TEXT[j].length())
					{
						for (int u = 0; u < ACTIVE_TITRES_MENU_ELEMENTS_AMOUNT; u++)
						{
							if (j == ACTIVE_TITRES_MENU_ELEMENTS_INDEXES[u]) {
								if (j == ACTIVE_TITRES_MENU_ELEMENTS_INDEXES[ACTIVE_TITRES_MENU_ELEMENTS_AMOUNT - 1])
								{
									return;
								}
							}
						}
					}
				}
			}
		}
	}
}