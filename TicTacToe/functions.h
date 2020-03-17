#include "constants.h"

int field[field_size][field_size];

int player = x_sign;
int comp = o_sign;

string difficulty = "EASY";

void start_filling() {
	for (int i = 0; i < field_size; i++)
	{
		for (int j = 0; j < field_size; j++)
		{
			field[i][j] = empty_sign;
		}
	}
}

void init() {
	system("title Tic-Tac-Toe");
	MoveWindow(GetConsoleWindow(), 0, 0, 0, 0, true);
	system(("mode con cols=" + to_string(cols) + " lines=" + to_string(lines)).c_str());
	srand(time(0));
	rand();
}

void hide_cursor() {
	CONSOLE_CURSOR_INFO cci;
	cci.bVisible = false;
	cci.dwSize = 100;
	SetConsoleCursorInfo(handle, &cci);
}

void set_cursor(COORD coord, int color) {
	SetConsoleTextAttribute(handle, color);
	SetConsoleCursorPosition(handle, coord);
}

void print_x(COORD& temp) {
	for (int i = 0; i < 7; i++)
	{
		set_cursor(temp, RED);
		cout << player_symbol[i];
		temp.Y++;
	}
}

void print_o(COORD& temp) {
	for (int i = 0; i < 7; i++)
	{
		set_cursor(temp, BLUE);
		cout << comp_symbol[i];
		temp.Y++;
	}
}

void print_grid() {
	COORD temp;
	for (int i = grid.Y; i < lines - 1; i++)
	{
		for (int j = grid.X; j < cols - 1; j++)
		{
			temp.X = j;
			temp.Y = i;
			if (i == grid.Y || i == grid.Y + h || i == grid.Y + 2 * h || i == lines - 2 ||
				j == grid.X || j == grid.X + w + 1 || j == grid.X + 2 * w + 2 || j == cols - 2) {
				set_cursor(temp, FULL_WHITE);
				cout << " ";
			}
		}
	}
}

void print_info() {
	COORD temp = info;
	if (difficulty == "START")
		set_cursor(temp, GREEN);
	else
		set_cursor(temp, WHITE);
	cout << "START";
	temp.X = cols - 5;
	if (difficulty == "EXIT")
		set_cursor(temp, GREEN);
	else
		set_cursor(temp, WHITE);
	cout << "EXIT";
	temp.X = info.X;
	temp.Y+=2;
	set_cursor(temp, WHITE);
	cout << "GAME DIFFICULTY: ";
	temp.X+=18;
	if(difficulty == "EASY")
		set_cursor(temp, GREEN);
	else 
		set_cursor(temp, WHITE);
	cout << "EASY";
	temp.X+=7;
	if (difficulty == "MID")
		set_cursor(temp, GREEN);
	else
		set_cursor(temp, WHITE);
	cout << "MID";
	temp.X += 7;
	if (difficulty == "HARD")
		set_cursor(temp, GREEN);
	else
		set_cursor(temp, WHITE);
	cout << "HARD";
}

void print_game_info() {
	COORD temp = info;
	temp.X += 15;
	set_cursor(temp, WHITE);
	cout << "GAME";
	temp.X = info.X;
	temp.Y+=2;
	set_cursor(temp, WHITE);
	cout << "GAME DIFFICULTY: ";
	temp.X += 18;
	if (difficulty == "EASY")
		set_cursor(temp, GREEN);
	else if (difficulty == "MID")
		set_cursor(temp, YELLOW);
	else if (difficulty == "HARD")
		set_cursor(temp, RED);
	cout << difficulty;
}

void repaint() {
	COORD temp;
	for (short i = 0; i < field_size; i++)
	{
		for (short j = 0; j < field_size; j++)
		{
			temp = { (grid.X + j * w + j + (short)1), (grid.Y + i * h + (short)1) };
			if (field[i][j] == player) {
				print_x(temp);
			}
			else if (field[i][j] == comp) {
				print_o(temp);
			}
		}
	}

}

void mode_choose() {
	HANDLE handle_in = GetStdHandle(STD_INPUT_HANDLE);
	SetConsoleMode(handle_in, ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
	const int events_count = 256;
	INPUT_RECORD all_events[events_count];
	DWORD read_event;

	bool flag = false;
	
	while (true)
	{
		ReadConsoleInput(handle_in, all_events, events_count, &read_event);
		for (int i = 0; i < read_event; i++)
		{
			c.X = all_events[i].Event.MouseEvent.dwMousePosition.X;
			c.Y = all_events[i].Event.MouseEvent.dwMousePosition.Y;

			if (all_events[i].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
			{
				if (c.Y == 2) {
					if (c.X >= info.X + 18 && c.X <= info.X + 21) {
						difficulty = "EASY";
						print_info();
						break;
					}
					else if (c.X >= info.X + 25 && c.X <= info.X + 27) {
						difficulty = "MID";
						print_info();
						break;
					}
					else if (c.X >= info.X + 32 && c.X <= info.X + 35) {
						difficulty = "HARD";
						print_info();
						break;
					}
				}
				else if (c.Y == info.Y && c.X >= info.X && c.X <= info.X + 4) {
					system("cls");
					print_game_info();
					flag = true;
					break;
				}
				else if (c.Y == info.Y && c.X >= cols - 5 && c.X <= cols - 2) {
					exit(0);
				}
				
			}
		}
		if (flag) {
			flag = false;
			break;
		}
	}
}

void shuffle(int arr[]) {
	for (int i = 0; i < field_size; i++)
	{
		arr[i] = rand() % 1000;
	}
}

bool is_array_equal(int arr[]) {
	for (int i = 0; i < field_size; i++)
	{
		for (int j = i + 1; j < field_size; j++)
		{
			if (arr[i] != arr[j])
				return false;
		}
	}
	return true;
}

bool is_draw() {
	for (int i = 0; i < field_size; i++)
	{
		for (int j = 0; j < field_size; j++)
		{
			if (field[i][j] == empty_sign)
				return false;
		}
	}
	return true;
}

int is_end() {
	for (int i = 0; i < field_size; i++)
	{
		int gorizontal[field_size];
		shuffle(gorizontal);
		for (int j = 0; j < field_size; j++)
		{
			if (field[i][j] != empty_sign)
				gorizontal[j] = field[i][j];
		}
		if (is_array_equal(gorizontal))
			return gorizontal[0];
	}
	for (int j = 0; j < field_size; j++)
	{
		int vertical[field_size];
		shuffle(vertical);
		for (int i = 0; i < field_size; i++)
		{
			if (field[i][j] != empty_sign)
				vertical[i] = field[i][j];
		}
		if (is_array_equal(vertical))
			return vertical[0];
	}
	int main_diagonal[field_size];
	shuffle(main_diagonal);
	for (int i = 0; i < field_size; i++)
	{
		if (field[i][i] != empty_sign)
			main_diagonal[i] = field[i][i];
		if (is_array_equal(main_diagonal))
			return main_diagonal[0];
	}
	int side_diagonal[field_size];
	shuffle(side_diagonal);
	for (int i = 0; i < field_size; i++)
	{
		if (field[i][field_size - 1 - i] != empty_sign)
			side_diagonal[i] = field[i][field_size - 1 - i];
		if (is_array_equal(side_diagonal))
			return side_diagonal[0];
	}
	if (is_draw())
		return draw;
	return not_end;
}

void player_move() {
	HANDLE handle_in = GetStdHandle(STD_INPUT_HANDLE);
	SetConsoleMode(handle_in, ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
	const int events_count = 256;
	INPUT_RECORD all_events[events_count];
	DWORD read_event;

	bool flag = false;

	while (true)
	{
		ReadConsoleInput(handle_in, all_events, events_count, &read_event);
		for (int i = 0; i < read_event; i++)
		{
			c.X = all_events[i].Event.MouseEvent.dwMousePosition.X;
			c.Y = all_events[i].Event.MouseEvent.dwMousePosition.Y;

			if (all_events[i].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
			{
				if (c.Y > grid.Y&& c.Y < grid.Y + h && c.X > grid.X&& c.X <= grid.X + w && field[0][0] == empty_sign) {
					field[0][0] = player;
					flag = true;
					break;
				}
				else if (c.Y > grid.Y&& c.Y < grid.Y + h && c.X > grid.X + w + 1 && c.X <= grid.X + 2 * w + 1 && field[0][1] == empty_sign) {
					field[0][1] = player;
					flag = true;
					break;
				}
				else if (c.Y > grid.Y&& c.Y < grid.Y + h && c.X > grid.X + 2 * w + 2 && c.X < cols - 2 && field[0][2] == empty_sign) {
					field[0][2] = player;
					flag = true;
					break;
				}
				else if (c.Y > grid.Y + h && c.Y < grid.Y + 2 * h && c.X > grid.X && c.X <= grid.X + w && field[1][0] == empty_sign) {
					field[1][0] = player;
					flag = true;
					break;
				}
				else if (c.Y > grid.Y + h && c.Y < grid.Y + 2 * h && c.X > grid.X + w + 1 && c.X <= grid.X + 2 * w + 1 && field[1][1] == empty_sign) {
					field[1][1] = player;
					flag = true;
					break;
				}
				else if (c.Y > grid.Y + h && c.Y < grid.Y + 2 * h && c.X > grid.X + 2 * w + 2 && c.X < cols - 2 && field[1][2] == empty_sign) {
					field[1][2] = player;
					flag = true;
					break;
				}
				else if (c.Y > grid.Y + 2 * h && c.Y < lines - 2 && c.X > grid.X && c.X <= grid.X + w && field[2][0] == empty_sign) {
					field[2][0] = player;
					flag = true;
					break;
				}
				else if (c.Y > grid.Y + 2 * h && c.Y < lines - 2 && c.X > grid.X + w + 1 && c.X <= grid.X + 2 * w + 1 && field[2][1] == empty_sign) {
					field[2][1] = player;
					flag = true;
					break;
				}
				else if (c.Y > grid.Y + 2 * h && c.Y < lines - 2 && c.X > grid.X + 2 * w + 2 && c.X < cols - 2 && field[2][2] == empty_sign) {
					field[2][2] = player;
					flag = true;
					break;
				}
			}
		}
		if (flag) {
			break;
		}
	}
}

void random_choose() {
	int last_i;
	int last_j;
	for (int i = 0; i < field_size; i++)
	{
		for (int j = 0; j < field_size; j++)
		{
			if (field[i][j] == empty_sign) {
				last_i = i;
				last_j = j;
				if (rand() % 2) {
					field[i][j] = comp;
					return;
				}
			}
		}
	}
	field[last_i][last_j] = comp;
	return;
}

int minimax(int depth, bool is_AI_turn) {
	if (is_end() == player)
		return PLAYER;
	else if (is_end() == comp)
		return COMP;
	else if (is_end() == draw)
		return DRAW;

	if (is_AI_turn) {
		int best_score = INT_MIN;
		for (int i = 0; i < field_size; i++)
		{
			for (int j = 0; j < field_size; j++)
			{
				if (field[i][j] == empty_sign) {
					field[i][j] = comp;
					int score = minimax(depth + 1, player_turn);
					field[i][j] = empty_sign;
					best_score = max(best_score, score);
				}
			}
		}
		return best_score;
	}
	else {
		int best_score = INT_MAX;
		for (int i = 0; i < field_size; i++)
		{
			for (int j = 0; j < field_size; j++)
			{
				if (field[i][j] == empty_sign) {
					field[i][j] = player;
					int score = minimax(depth + 1, ai_turn);
					field[i][j] = empty_sign;
					best_score = min(best_score, score);
				}
			}
		}
		return best_score;
	}
}

void comp_move() {
	if (difficulty == "EASY" || difficulty == "MID") {
		random_choose();
	}
	else if (difficulty == "HARD") {
		COORD move;
		int best_score = INT_MIN;
		for (int i = 0; i < field_size; i++)
		{
			for (int j = 0; j < field_size; j++)
			{
				if (field[i][j] == empty_sign) {
					field[i][j] = comp;
					int score = minimax(0, player_turn);
					field[i][j] = empty_sign;
					if (score > best_score) {
						best_score = score;
						move.X = j;
						move.Y = i;
					}
				}
			}
		}
		field[move.Y][move.X] = comp;
	}
}

void gameover(int winner) {
	string s;
	if (winner == player) {
		s = "YOU WON!";
	}
	else if (winner == comp)
		s = "YOU LOST!";
	else if (winner == draw)
		s = "IT'S A TIE!";
	else if (winner == not_end)
		return;
	MessageBoxA(0, s.c_str(), "GAMEOVER", MB_OK);
	system("cls");
	exit(0);
}







void game() {
	print_info();
	mode_choose();
	print_grid();

	while (true) {
		player_move();
		repaint();
		gameover(is_end());
		comp_move();
		repaint();
		gameover(is_end());
	}
}


