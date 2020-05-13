#pragma once
#include <iostream>
#include <string>

#include "menu.h"

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
	int size = 0;
	MenuElement* mas = new MenuElement[size];
	read_elements(mas, size, path);
	print_menu(mas, size);
	track_mouse(mas, size, titres_action);
}
