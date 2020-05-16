#pragma once
#include <iostream>
#include <string>

#include "Menu.h"

using namespace std;

bool options_action(int index)
{
	switch (index)
	{
	case 2:
		difficulty = Difficulties::EASY;
		break;
	case 3:
		difficulty = Difficulties::MID;
		break;
	case 4:
		difficulty = Difficulties::HARD;
		break;
	case 6:
		whos_first_turn = Turns::PLAYER_TURN;
		break;
	case 7:
		whos_first_turn = Turns::COMP_TURN;
		break;
	case 9:
		player_value = Signs::X_SIGN;
		computer_value = Signs::O_SIGN;
		break;
	case 10:
		player_value = Signs::O_SIGN;
		computer_value = Signs::X_SIGN;
		break;
	case 11:
		return true;
	default:
		break;
	}
	return false;
}

void call_options_menu()
{
	string path = "options_menu.txt";
	MenuBar mb;
	mb.mas = new MenuElement[mb.size];
	read_elements(mb, path);
	print_menu(mb);
	track_mouse(mb, options_action);
}
