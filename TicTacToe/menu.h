#pragma once
#include <iostream>
#include <string>
#include <Windows.h>

#include "constants.h"
#include "settings.h"
#include "IO.h"

using namespace std;

struct MenuElement
{
	string text;
	COORD pos;
	bool is_active;
	bool is_pressed = false;
};

void read_elements(MenuElement*& mas, int& size, string path)
{
	FILE* f;
	fopen_s(&f, path.c_str(), "r");
	char* help = new char[100];
	while (true)
	{
		fgets(help, 100, f);
		size++;
		if (feof(f))
			break;
	}
	delete[] help;
	fclose(f);
	delete[] mas;
	mas = new MenuElement[size];
	fopen_s(&f, path.c_str(), "r");
	int i = 0;
	char* temp_str = new char[100];
	while (true)
	{
		mas[i].pos.Y = fgetc(f) % 48;
		mas[i].is_active = convert_char_to_bool(fgetc(f));
		fgets(temp_str, 100, f);
		mas[i].text = temp_str;
		if (compare_str(mas[i].text, convert_difficulty_to_string(difficulty)) || compare_str(mas[i].text, convert_turn_to_string(whos_first_turn)) ||
			compare_str(mas[i].text, convert_sign_to_char(player_value)))
			mas[i].is_pressed = true;
		if (i == 0 || i == size - 1)
		{
			mas[i].pos.X = (43 - mas[i].text.length()) / 2;
		}
		else if (mas[i].pos.Y == mas[i - 1].pos.Y)
		{
			mas[i].pos.X = mas[i - 1].pos.X + mas[i - 1].text.length() + 1;
		}
		else
		{
			mas[i].pos.X = 0;
		}
		i++;
		if (feof(f) || i == size)
			break;
	}
	fclose(f);
}

void print_menu(MenuElement*& mas, int size)
{
	system("cls");
	for (int i = 0; i < size; i++)
	{
		set_cursor_position(mas[i].pos);
		if(mas[i].is_pressed)
			set_cursor_color(GREEN);
		else
			set_cursor_color(WHITE);
		cout << mas[i].text;
	}
	set_cursor_color(WHITE);
}

void track_mouse(MenuElement*& mas, int size, bool (*action)(int))
{
	HANDLE handle_in = GetStdHandle(STD_INPUT_HANDLE);
	SetConsoleMode(handle_in, ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
	const int events_count = 256;
	INPUT_RECORD all_events[events_count];
	DWORD read_event;

	COORD c;

	bool is_quit = false;
	MenuElement* prev;
	MenuElement* present;

	while (true)
	{
		ReadConsoleInput(handle_in, all_events, events_count, &read_event);
		for (int i = 0; i < read_event; i++)
		{
			c.X = all_events[i].Event.MouseEvent.dwMousePosition.X;
			c.Y = all_events[i].Event.MouseEvent.dwMousePosition.Y;

			if (all_events[i].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
			{
				for (int j = 0; j < size; j++)
				{
					if (c.Y == mas[j].pos.Y && c.X >= mas[j].pos.X && c.X < mas[j].pos.X + mas[j].text.length() && mas[j].is_active)
					{
						is_quit = action(j);
						if (is_quit)
							return;
						prev = &mas[0];
						int l = j;
						int r = j;
						while (mas[l].pos.Y == mas[j].pos.Y || mas[r].pos.Y == mas[j].pos.Y)
						{
							if (mas[l].pos.Y == mas[j].pos.Y)
							{
								if (mas[l].is_pressed == true)
								{
									prev = &mas[l];
									break;
								}
								l--;
							}
							if (mas[r].pos.Y == mas[r].pos.Y)
							{
								if (mas[r].is_pressed == true)
								{
									prev = &mas[r];
									break;
								}
								r++;
							}
						}
						present = &mas[j];

						prev->is_pressed = false;
						set_cursor_color(WHITE);
						set_cursor_position(prev->pos);
						cout << prev->text;

						present->is_pressed = true;
						set_cursor_color(GREEN);
						set_cursor_position(present->pos);
						cout << present->text;

						set_cursor_color(WHITE);
					}
				}
			}
		}
	}
}
