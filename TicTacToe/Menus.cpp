#include <iostream>
#include <string>

#include "MyMenu.h"
#include "Menus.h"
#include "Settings.h"
#include "Constants.h"

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

void open_options_menu()
{
	MenuBar mb = call_menu("options_menu.txt");
	track_mouse(mb, options_action);
}

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

void open_titres_menu()
{
	MenuBar mb = call_menu("titres_menu.txt");
	track_mouse(mb, titres_action);
}

MenuBar call_game_menu()
{
	return call_menu("game_menu.txt");
}