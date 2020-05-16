#pragma once
#include <iostream>
#include <string>
#include <Windows.h>

using namespace std;

struct MenuElement
{
	string text;
	COORD pos;
	bool is_active;
	bool is_pressed = false;
};

struct MenuBar
{
	MenuElement* mas;
	int size = 0;
};

void read_elements(MenuBar& mb, string path);

void print_menu(MenuBar mb);

void track_mouse(MenuBar& mb, bool (*action)(int));

MenuBar call_menu(string path);


