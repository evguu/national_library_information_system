#include "pch.h"
#include <Windows.h>
#include <locale>
#include "Console.h"

namespace Utils
{
	void setupResolution()
	{
		SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, nullptr);
		system("MODE CON: COLS=256 LINES=100");
	}

	void setupEncoding()
	{
		setlocale(LC_ALL, "rus");
		SetConsoleCP(1251);
		SetConsoleOutputCP(1251);
	}
}
