#pragma once
#include <iostream>
#include <Windows.h>

#include "settings.h"
#include "constants.h"
#include "IO.h"
#include "Menu.h"

using namespace std;

MenuBar call_game_menu()
{
	string path = "game_menu.txt";
	MenuBar mb;
	mb.mas = new MenuElement[mb.size];
	read_elements(mb, path);
	print_menu(mb);
	return mb;
}