#pragma once
#include <iostream>
#include <string>

#include "Menu.h"

using namespace std;

bool titres_action(int index)
{
	switch (index)
	{
	case 2:
		return true;
	default:
		break;
	}
	return false;
}

void call_titres_menu()
{
	string path = "titres_menu.txt";
	MenuBar mb;
	mb.mas = new MenuElement[mb.size];
	read_elements(mb, path);
	print_menu(mb);
	track_mouse(mb, titres_action);
}
