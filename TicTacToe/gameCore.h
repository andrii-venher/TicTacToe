#pragma once
#include <iostream>
#include <Windows.h>
#include <string>
#include <ctime>

#include "constants.h"
#include "settings.h"
#include "optionsMenu.h"
#include "gameMenu.h"
#include "aboutGame.h"
#include "IO.h"

using namespace std;

void clear_field();

void move(int& last_move);
void computer_move();
COORD random_choice();
COORD best_choice(turns t, signs sign);
int minimax(int depth, bool is_comp_turn);

void start_mouse_track();
void get_hint();

int get_state();

void gameover(int state);

COORD convert_indexes_to_coordinates(COORD move);
states convert_to_state(signs sign);

void game();
void play_match();

//fills field with empty values
void clear_field() 
{
	for (int i = 0; i < FIELD_SIZE; i++)
	{
		for (int j = 0; j < FIELD_SIZE; j++)
		{
			field[i][j] = empty_value;
		}
	}
}

//convertes value of place to a state of game
states convert_to_state(signs sign)
{
	if (sign == empty_value)
	{
	return states::NOT_END;
	}
	else if (sign == player_value)
	{
		return states::PLAYER_WON;
	}
	else if (sign == comp_value)
	{
		return states::COMP_WON;
	}
	
}

//convertes indexes of field array to coordinates of screen
COORD convert_indexes_to_coordinates(COORD move)
{
	return GRID_POSITIONS[move.Y][move.X];
}

//returns state of a match
int get_state() {
	//check rows
	for (int i = 0; i < FIELD_SIZE; i++)
	{
		for (int j = 1; j < FIELD_SIZE; j++)
		{
			if (field[i][j] != field[i][j - 1] || field[i][j] == empty_value || field[i][j - 1] == empty_value)
			{
				break;
			}
			if (j == FIELD_SIZE - 1) 
			{
				
				return convert_to_state(field[i][j]);
			}
		}
	}

	//check columns
	for (int j = 0; j < FIELD_SIZE; j++)
	{
		for (int i = 1; i < FIELD_SIZE; i++)
		{
			if (field[i][j] != field[i - 1][j] || field[i][j] == empty_value || field[i - 1][j] == empty_value)
			{
				break;
			}
			if (i == FIELD_SIZE - 1)
			{
				return convert_to_state(field[i][j]);
			}
		}
	}
	
	//check main diagonal
	for (int i = 1; i < FIELD_SIZE; i++)
	{
		if (field[i][i] != field[i - 1][i - 1] || field[i][i] == empty_value || field[i - 1][i - 1] == empty_value)
		{
			break;
		}
		if (i == FIELD_SIZE - 1)
		{
			return convert_to_state(field[i][i]);
		}
	}

	//check side diagonal
	for (int i = 1; i < FIELD_SIZE; i++)
	{
		if (field[i][FIELD_SIZE - 1 - i] != field[i - 1][FIELD_SIZE - i] || field[i][FIELD_SIZE - 1 - i] == empty_value
			|| field[i - 1][FIELD_SIZE - i] == empty_value)
		{
			break;
		}
		if (i == FIELD_SIZE - 1)
		{
			return convert_to_state(field[i][FIELD_SIZE - 1 - i]);
		}
	}
	
	//check for draw
	for (int i = 0; i < FIELD_SIZE; i++)
	{
		for (int j = 0; j < FIELD_SIZE; j++)
		{
			if (field[i][j] == empty_value)
				return convert_to_state(field[i][j]);
		}
	}
	return states::DRAW_STATE;
}

//makes a move depending on who moved before
void move(int& last_move) {
	if (last_move == turns::PLAYER_TURN)
	{
		computer_move();
		last_move = turns::COMP_TURN;
	}
	else
	{
		start_mouse_track();
		last_move = turns::PLAYER_TURN;
	}
}

//tracks all player mouse actions (moves, clicks on buttons)
void start_mouse_track()
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
		for (int event_index = 0; event_index < read_event; event_index++)
		{
			c.X = all_events[event_index].Event.MouseEvent.dwMousePosition.X;
			c.Y = all_events[event_index].Event.MouseEvent.dwMousePosition.Y;

			if (all_events[event_index].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
			{
				for (int i = 0; i < FIELD_SIZE; i++)
				{
					for (int j = 0; j < FIELD_SIZE; j++)
					{
						if (c.X >= GRID_POSITIONS[i][j].X && c.X <= GRID_POSITIONS[i][j].X + IMAGE_WIDTH &&
							c.Y >= GRID_POSITIONS[i][j].Y && c.Y <= GRID_POSITIONS[i][j].Y + IMAGE_HEIGHT &&
							field[i][j] == empty_value)
						{
							field[i][j] = player_value;
							return;
						}
					}
				}
				for (int j = 0; j < GAME_MENU_ELEMENTS_AMOUNT; j++)
				{
					if (c.Y == GAME_MENU_POSITION[j].Y && c.X >= GAME_MENU_POSITION[j].X && c.X < GAME_MENU_POSITION[j].X + GAME_MENU_TEXT[j].length())
					{
						for (int u = 0; u < ACTIVE_GAME_MENU_ELEMENTS_AMOUNT; u++)
						{
							if (j == ACTIVE_GAME_MENU_ELEMENTS_INDEXES[u])
							{
								if (j == ACTIVE_GAME_MENU_ELEMENTS_INDEXES[0])
								{
									play_match();
								}
								else if (j == ACTIVE_GAME_MENU_ELEMENTS_INDEXES[1])
								{
									call_options_menu();
									game();
								}
								else if (j == ACTIVE_GAME_MENU_ELEMENTS_INDEXES[2] && isMatch)
								{
									get_hint();
								}
								else if (j == ACTIVE_GAME_MENU_ELEMENTS_INDEXES[3])
								{
									call_titres_menu();
									game();
								}
							}
						}
					}
				}
			}
		}
	}
}

//indicates a preferable place on the field
void get_hint()
{
	if (hints > 0)
	{
		hints--;
		print_info();
		COORD move;
		move = best_choice(turns::PLAYER_TURN, player_value);
		for (int i = 0; i < 3; i++)
		{
			print_sign(convert_indexes_to_coordinates(move), signs::HINT);
			Sleep(200);
			print_sign(convert_indexes_to_coordinates(move), signs::EMPTY_SIGN);
			Sleep(200);
		}
	}
}

//depending on the difficulty chooses a move of computer
void computer_move()
{
	COORD move;
	if (difficulty == difficulties::EASY)
	{
		move = random_choice();
	}
	else if (difficulty == difficulties::MID)
	{
		if (rand() % 2)
		{
			move = random_choice();
		}
		else
		{
			move = best_choice(turns::COMP_TURN, comp_value);
		}
	}
	else if (difficulty == difficulties::HARD)
	{
		move = best_choice(turns::COMP_TURN, comp_value);
	}
	field[move.Y][move.X] = comp_value;
}

//returns a random empty place
COORD random_choice() {
	int count = 0;
	
	for (int i = 0; i < FIELD_SIZE; i++)
	{
		for (int j = 0; j < FIELD_SIZE; j++)
		{
			if (field[i][j] == empty_value) {
				count++;
			}
		}
	}

	COORD* possible_moves = new COORD[count];

	int k = 0;
	for (int i = 0; i < FIELD_SIZE; i++)
	{
		for (int j = 0; j < FIELD_SIZE; j++)
		{
			if (field[i][j] == empty_value) {
				possible_moves[k] = { (short)j, (short)i };
				k++;
			}
		}
	}
	
	int index = rand() % count;

	COORD move = possible_moves[index];

	delete[] possible_moves;
	return move;
}

//retruns preferable place
COORD best_choice(turns t, signs sign)
{
	COORD move;
	int best_score; 
	if (t == turns::COMP_TURN)
	{
		best_score = INT_MIN;
		for (int i = 0; i < FIELD_SIZE; i++)
		{
			for (int j = 0; j < FIELD_SIZE; j++)
			{
				if (field[i][j] == empty_value) {
					field[i][j] = sign;
					int score = minimax(0, t);
					field[i][j] = empty_value;
					if (score > best_score) {
						best_score = score;
						move.X = j;
						move.Y = i;
					}
				}
			}
		}
	} 
	else
	{
		best_score = INT_MAX;
		for (int i = 0; i < FIELD_SIZE; i++)
		{
			for (int j = 0; j < FIELD_SIZE; j++)
			{
				if (field[i][j] == empty_value) {
					field[i][j] = sign;
					int score = minimax(0, t);
					field[i][j] = empty_value;
					if (score < best_score) {
						best_score = score;
						move.X = j;
						move.Y = i;
					}
				}
			}
		}
	}
	return move;
}

//algorithm of searching for preferable place
int minimax(int depth, bool is_comp_turn) {
	int state = get_state();

	if (state == states::PLAYER_WON)
		return scores::PLAYER_SCORE;
	else if (state == states::COMP_WON)
		return scores::COMP_SCORE;
	else if (state == states::DRAW_STATE)
		return scores::DRAW_SCORE;

	if (is_comp_turn) {
		int best_score = INT_MIN;
		for (int i = 0; i < FIELD_SIZE; i++)
		{
			for (int j = 0; j < FIELD_SIZE; j++)
			{
				if (field[i][j] == empty_value) {
					field[i][j] = comp_value;
					int score = minimax(depth + 1, !is_comp_turn);
					field[i][j] = empty_value;
					best_score = max(best_score, score);
				}
			}
		}
		return best_score;
	}
	else {
		int best_score = INT_MAX;
		for (int i = 0; i < FIELD_SIZE; i++)
		{
			for (int j = 0; j < FIELD_SIZE; j++)
			{
				if (field[i][j] == empty_value) {
					field[i][j] = player_value;
					int score = minimax(depth + 1, !is_comp_turn);
					field[i][j] = empty_value;
					best_score = min(best_score, score);
				}
			}
		}
		return best_score;
	}
}

//after reaching of end situation shows a winner or a draw in message box and calls a new game
void gameover(int state) {
	if (state == states::NOT_END)
	{
		return;
	}
	
	string s;
	
	if (state == states::PLAYER_WON) 
	{
		s = "YOU WON!";
		player_points++;
	}
	else if (state == states::COMP_WON)
	{
		s = "YOU LOST!";
		comp_points++;
	}
	else if (state == states::DRAW_STATE)
	{
		s = "IT'S A DRAW!";
	}

	isMatch = false;
	
	MessageBoxA(0, s.c_str(), "GAMEOVER", MB_OK);
	game();
}

//starts a new match
void play_match()
{
	int state = states::NOT_END;
	int last_move = !whos_first_turn;
	isMatch = true;
	hints = 3;

	clear_field();
	print_grid();
	repaint_field();
	print_info();

	while (state == states::NOT_END)
	{
		move(last_move);
		repaint_field();
		print_info();
		state = get_state();
	}

	gameover(state);
}

//calls a new game
void game() {
	system("cls");

	call_game_menu();
	fill_grid_positions();
	print_grid();
	print_info();
	start_mouse_track();
}


