#include <iostream>
#include <Windows.h>

#include "MouseTrack.h"

using namespace std;

COORD click_coordinate()
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
				return c;
			}
		}
	}
}