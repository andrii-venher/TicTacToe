#include <iostream>
#include <Windows.h>
#include <string>
#include <ctime>

#include "Constants.h"
#include "Settings.h"
#include "IO.h"
#include "MouseTrack.h"
#include "MyMenu.h"
#include "Menus.h"
#include "Core.h"

using namespace std;

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
States convert_to_state(Signs sign)
{
	if (sign == empty_value)
	{
		return States::NOT_END;
	}
	else if (sign == player_value)
	{
		return States::PLAYER_WON;
	}
	else if (sign == computer_value)
	{
		return States::COMP_WON;
	}

}

//convertes indexes of field array to coordinates of screen
COORD convert_indexes_to_coordinates(COORD move)
{
	return grid_pos[move.Y][move.X];
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
	return States::DRAW_STATE;
}

//tracks all player mouse actions on game screen (moves, clicks on buttons)
void game_mouse_track(MenuBar mb)
{
	COORD click;
	while (true)
	{
		click = click_coordinate();
		for (int i = 0; i < FIELD_SIZE; i++)
		{
			for (int j = 0; j < FIELD_SIZE; j++)
			{
				if (click.X >= grid_pos[i][j].X && click.X <= grid_pos[i][j].X + IMAGE_WIDTH &&
					click.Y >= grid_pos[i][j].Y && click.Y <= grid_pos[i][j].Y + IMAGE_HEIGHT &&
					field[i][j] == empty_value)
				{
					field[i][j] = player_value;
					return;
				}
			}
		}
		for (int j = 0; j < mb.size; j++)
		{
			if (click.Y == mb.mas[j].pos.Y && click.X >= mb.mas[j].pos.X && click.X < mb.mas[j].pos.X + mb.mas[j].text.length() && mb.mas[j].is_active)
			{
				switch (j)
				{
				case 1:
					play_match(mb);
					break;
				case 2:
					open_options_menu();
					game();
					break;
				case 3:
					if (is_match)
						get_hint();
					break;
				case 4:
					open_titres_menu();
					game();
					break;
				default:
					break;
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
		move = best_choice(Turns::PLAYER_TURN, player_value);
		for (int i = 0; i < 3; i++)
		{
			print_sign(convert_indexes_to_coordinates(move), Signs::HINT);
			Sleep(150);
			print_sign(convert_indexes_to_coordinates(move), Signs::EMPTY_SIGN);
			Sleep(150);
		}
	}
}

//depending on the difficulty chooses a move of computer
void computer_move()
{
	COORD move;
	if (difficulty == Difficulties::EASY)
	{
		move = random_choice();
	}
	else if (difficulty == Difficulties::MID)
	{
		if (rand() % 2)
		{
			move = random_choice();
		}
		else
		{
			move = best_choice(Turns::COMP_TURN, computer_value);
		}
	}
	else if (difficulty == Difficulties::HARD)
	{
		move = best_choice(Turns::COMP_TURN, computer_value);
	}
	field[move.Y][move.X] = computer_value;
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
COORD best_choice(Turns t, Signs sign)
{
	COORD move;
	int best_score;
	if (t == Turns::COMP_TURN)
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

	if (state == States::PLAYER_WON)
		return Scores::PLAYER_SCORE;
	else if (state == States::COMP_WON)
		return Scores::COMP_SCORE;
	else if (state == States::DRAW_STATE)
		return Scores::DRAW_SCORE;

	if (is_comp_turn) {
		int best_score = INT_MIN;
		for (int i = 0; i < FIELD_SIZE; i++)
		{
			for (int j = 0; j < FIELD_SIZE; j++)
			{
				if (field[i][j] == empty_value) {
					field[i][j] = computer_value;
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

//after reaching the end situation shows a winner or a draw in message box and calls a new game
void gameover(int state) {
	if (state == States::NOT_END)
	{
		return;
	}

	string s;

	if (state == States::PLAYER_WON)
	{
		s = "YOU WON!";
		player_points++;
	}
	else if (state == States::COMP_WON)
	{
		s = "YOU LOST!";
		computer_points++;
	}
	else if (state == States::DRAW_STATE)
	{
		s = "IT'S A DRAW!";
	}

	is_match = false;

	MessageBoxA(0, s.c_str(), "GAMEOVER", MB_OK);
	game();
}

//starts a new match
void play_match(MenuBar mb)
{
	int state = States::NOT_END;
	int last_move = !whos_first_turn;
	is_match = true;
	hints = 3;

	clear_field();
	print_grid();
	repaint_field();
	print_info();

	while (state == States::NOT_END)
	{
		if (last_move == Turns::PLAYER_TURN)
		{
			computer_move();
			last_move = Turns::COMP_TURN;
		}
		else
		{
			game_mouse_track(mb);
			last_move = Turns::PLAYER_TURN;
		}
		repaint_field();
		print_info();
		state = get_state();
	}

	gameover(state);
}

//calls a new game
void game() {
	system("cls");

	MenuBar game_menu = call_game_menu();
	fill_grid_positions();
	print_grid();
	print_info();
	game_mouse_track(game_menu);
}
