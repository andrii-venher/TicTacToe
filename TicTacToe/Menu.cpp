#include <iostream>
#include <string>
#include <Windows.h>

#include "constants.h"
#include "settings.h"
#include "IO.h"
#include "MouseTrack.h"
#include "Menu.h"

using namespace std;

void read_elements(MenuBar& mb, string path)
{
	FILE* f;
	fopen_s(&f, path.c_str(), "r");
	char* help = new char[100];
	while (true)
	{
		fgets(help, 100, f);
		mb.size++;
		if (feof(f))
			break;
	}
	delete[] help;
	fclose(f);
	delete[] mb.mas;
	mb.mas = new MenuElement[mb.size];
	fopen_s(&f, path.c_str(), "r");
	int i = 0;
	char* temp_str = new char[100];
	while (true)
	{
		mb.mas[i].pos.Y = fgetc(f) % 48;
		mb.mas[i].is_active = convert_char_to_bool(fgetc(f));
		fgets(temp_str, 100, f);
		mb.mas[i].text = temp_str;
		if (compare_str(mb.mas[i].text, convert_difficulty_to_string(difficulty)) || compare_str(mb.mas[i].text, convert_turn_to_string(whos_first_turn)) ||
			compare_str(mb.mas[i].text, convert_sign_to_char(player_value)))
			mb.mas[i].is_pressed = true;
		if (i == 0 || i == mb.size - 1)
		{
			mb.mas[i].pos.X = (FIELD_WIDTH - mb.mas[i].text.length()) / 2;
		}
		else if (mb.mas[i].pos.Y == mb.mas[i - 1].pos.Y)
		{
			mb.mas[i].pos.X = mb.mas[i - 1].pos.X + mb.mas[i - 1].text.length() + 1;
		}
		else
		{
			mb.mas[i].pos.X = 0;
		}
		i++;
		if (feof(f) || i == mb.size)
			break;
	}
	fclose(f);
}

void print_menu(MenuBar mb)
{
	system("cls");
	for (int i = 0; i < mb.size; i++)
	{
		set_cursor_position(mb.mas[i].pos);
		if (mb.mas[i].is_pressed)
			set_cursor_color(GREEN);
		else
			set_cursor_color(WHITE);
		cout << mb.mas[i].text;
	}
	set_cursor_color(WHITE);
}

void track_mouse(MenuBar& mb, bool (*action)(int))
{
	bool is_quit = false;
	MenuElement* prev;
	MenuElement* present;
	COORD click;
	while (true)
	{
		click = click_coordinate();
		for (int j = 0; j < mb.size; j++)
		{
			if (click.Y == mb.mas[j].pos.Y && click.X >= mb.mas[j].pos.X && click.X < mb.mas[j].pos.X + mb.mas[j].text.length() && mb.mas[j].is_active)
			{
				is_quit = action(j);
				if (is_quit)
					return;
				prev = &(mb.mas[0]);
				int l = j;
				int r = j;
				while (mb.mas[l].pos.Y == mb.mas[j].pos.Y || mb.mas[r].pos.Y == mb.mas[j].pos.Y)
				{
					if (mb.mas[l].pos.Y == mb.mas[j].pos.Y)
					{
						if (mb.mas[l].is_pressed == true)
						{
							prev = &(mb.mas[l]);
							break;
						}
						l--;
					}
					if (mb.mas[r].pos.Y == mb.mas[r].pos.Y)
					{
						if (mb.mas[r].is_pressed == true)
						{
							prev = &(mb.mas[r]);
							break;
						}
						r++;
					}
				}
				present = &(mb.mas[j]);

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
