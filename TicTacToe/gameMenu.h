#pragma once
#include <iostream>
#include <Windows.h>

#include "settings.h"
#include "constants.h"
#include "IO.h"

using namespace std;

void call_game_menu();
void fill_game_menu_position(COORD pos[]);
void print_game_menu();

//fills game menu elements` positions and prints game menu
void call_game_menu()
{
	fill_game_menu_position(GAME_MENU_POSITION);
	print_game_menu();
}

//gives positions on screen to elements of game menu
void fill_game_menu_position(COORD pos[]) {
	pos[0] = { 0, 0 };
	for (short i = 1; i < GAME_MENU_ELEMENTS_AMOUNT; i++)
	{
		pos[i] = { pos[i - 1].X + short(GAME_MENU_TEXT[i - 1].length() + MENU_TEXT_SHIFT), pos[i - 1].Y };
	}
}

//prints game menu on screen
void print_game_menu()
{
	system("cls");
	set_cursor_color(WHITE);
	for (int i = 0; i < GAME_MENU_ELEMENTS_AMOUNT; i++)
	{
		set_cursor_position(GAME_MENU_POSITION[i]);
		cout << GAME_MENU_TEXT[i];
	}
}

