#include <iostream>
#include <Windows.h>
#include <string>

using namespace std;

HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
HANDLE handle_in = GetStdHandle(STD_INPUT_HANDLE);

COORD c;
COORD grid = { 1, 4 };
COORD info = { 1, 0 };

const int events_count = 256;
INPUT_RECORD all_events[events_count];
DWORD read_event;


const int cols = 39;
const int lines = 30;
int w = (cols - 2 - 4) / 3;
int h = (lines - 1 - grid.Y) / 3;

int field[3][3] = {};

bool flag = false;

string difficulty = "EASY";


string player_symbol[7] = { "  *     *  " , 
							"   *   *   " , 
							"    * *    " , 
							"     *     " , 
							"    * *    " , 
							"   *   *   " , 
							"  *     *  " };

enum colors { FULL_WHITE = 255, WHITE = 7, RED = 12, BLUE = 9, GREEN = 10, YELLOW = 14};

void init() {
	system("title Tic-Tac-Toe");
	MoveWindow(GetConsoleWindow(), 0, 0, 0, 0, true);
	system(("mode con cols=" + to_string(cols) + " lines=" + to_string(lines)).c_str());
	SetConsoleMode(handle_in, ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
}

void set_cursor(COORD coord, int color) {
	SetConsoleTextAttribute(handle, color);
	SetConsoleCursorPosition(handle, coord);
}

void hide_cursor() {
	CONSOLE_CURSOR_INFO cci;
	cci.bVisible = false;
	cci.dwSize = 100;
	SetConsoleCursorInfo(handle, &cci);
}

/*void testColor() {
	for (int i = 0; i <= 256; i++)
	{
		SetConsoleTextAttribute(handle, i);
		cout << i << endl;
	}

}*/

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

void mode_choose() {
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

void print_x(COORD &temp) {
	for (int i = 0; i < 7; i++)
	{
		set_cursor(temp, RED);
		cout << player_symbol[i];
		temp.Y++;
	}
}

void player_move() {
	flag = false;
	while (true)
	{
		ReadConsoleInput(handle_in, all_events, events_count, &read_event);
		for (int i = 0; i < read_event; i++)
		{
			c.X = all_events[i].Event.MouseEvent.dwMousePosition.X;
			c.Y = all_events[i].Event.MouseEvent.dwMousePosition.Y;

			if (all_events[i].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
			{
				if (c.Y > grid.Y&& c.Y < grid.Y + h && c.X > grid.X&& c.X <= grid.X + w && field[0][0] != 2) {
					COORD temp = { grid.X + 1, grid.Y + 1 };
					print_x(temp);
					field[0][0] = 1;
					flag = true;
					break;
				}
				else if (c.Y > grid.Y&& c.Y < grid.Y + h && c.X > grid.X + w + 1 && c.X <= grid.X + 2 * w + 1 && field[0][1] != 2) {
					COORD temp = { grid.X + w + 2, grid.Y + 1 };
					print_x(temp);
					field[0][1] = 1;
					flag = true;
					break;
				}
				else if (c.Y > grid.Y&& c.Y < grid.Y + h && c.X > grid.X + 2 * w + 2 && c.X < cols - 2 && field[0][2] != 2) {
					COORD temp = { grid.X + 2 * w + 3, grid.Y + 1 };
					print_x(temp);
					field[0][2] = 1;
					flag = true;
					break;
				}
				else if (c.Y > grid.Y + h && c.Y < grid.Y + 2 * h && c.X > grid.X && c.X <= grid.X + w && field[1][0] != 2) {
					COORD temp = { grid.X + 1, grid.Y + h + 1 };
					print_x(temp);
					field[1][0] = 1;
					flag = true;
					break;
				}
				else if (c.Y > grid.Y + h && c.Y < grid.Y + 2 * h && c.X > grid.X + w + 1 && c.X <= grid.X + 2 * w + 1 && field[1][1] != 2) {
					COORD temp = { grid.X + w + 2, grid.Y + h + 1 };
					print_x(temp);
					field[1][1] = 1;
					flag = true;
					break;
				}
				else if (c.Y > grid.Y + h && c.Y < grid.Y + 2 * h && c.X > grid.X + 2 * w + 2 && c.X < cols - 2 && field[1][2] != 2) {
					COORD temp = { grid.X + 2 * w + 3, grid.Y + h + 1 };
					print_x(temp);
					field[1][2] = 1;
					flag = true;
					break;
				}
				else if (c.Y > grid.Y + 2 * h && c.Y < lines - 2 && c.X > grid.X && c.X <= grid.X + w && field[2][0] != 2) {
					COORD temp = { grid.X + 1, grid.Y + 2 * h + 1 };
					print_x(temp);
					field[2][0] = 1;
					flag = true;
					break;
				}
				else if (c.Y > grid.Y + 2 * h && c.Y < lines - 2 && c.X > grid.X + w + 1 && c.X <= grid.X + 2 * w + 1 && field[2][1] != 2) {
					COORD temp = { grid.X + w + 2, grid.Y + 2 * h + 1 };
					print_x(temp);
					field[2][1] = 1;
					flag = true;
					break;
				}
				else if (c.Y > grid.Y + 2 * h && c.Y < lines - 2 && c.X > grid.X + 2 * w + 2 && c.X < cols - 2 && field[2][2] != 2) {
					COORD temp = { grid.X + 2 * w + 3, grid.Y + 2 * h + 1 };
					print_x(temp);
					field[2][2] = 1;
					flag = true;
					break;
				}
			}
		}
		if (flag) {
			flag = false;
			break;
		}
	}
}

void game() {
	print_info();
	mode_choose();
	print_grid();
	player_move();
}

int main() {
	init();

	hide_cursor();

	game();

	getchar();

	system("pause < NUL");
}
