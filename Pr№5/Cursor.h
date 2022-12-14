#pragma once

#include <Windows.h>

class Cursor
{
	public:
		static void GoToXY(int x, int y);
		static COORD GetConsoleCursorPosition();
};

