#include "pch.h"
#include <Windows.h>
#include <locale>
#include "Console.h"
#include <iostream>

const int col = 128;
const int lines = 40;

namespace Utils
{
	void setupResolution()
	{
		//SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, nullptr);
		system(("MODE CON: COLS=" + to_string(col+1) + " LINES=" + to_string(lines+1)).c_str());
		void* handle = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_CURSOR_INFO structCursorInfo;
		GetConsoleCursorInfo(handle, &structCursorInfo);
		structCursorInfo.bVisible = FALSE;
		SetConsoleCursorInfo(handle, &structCursorInfo);
		ShowCursor(FALSE);
	}

	void setupEncoding()
	{
		setlocale(LC_ALL, "rus");
		SetConsoleCP(1251);
		SetConsoleOutputCP(1251);
	}

	void noBlinkOutput(string src)
	{
		char res[lines][col];
		int line = 0;
		int pos = 0;
		for (auto i : src)
		{
			if (i == '\n')
			{
				while (pos != col - 1)
				{
					res[line][pos++] = ' ';
				}
				res[line][pos++] = '\n';
				++line;
				pos = 0;
			}
			else
			{
				if (pos < col - 1)
				{
					res[line][pos++] = i;
				}
				else
				{
					res[line][col - 4] = '.';
					res[line][col - 3] = '.';
					res[line][col - 2] = '.';
					res[line][col - 1] = '\n';
					++line;
					pos = 0;
				}
			}
		}
		while (line < lines)
		{
			while (pos != col - 1)
			{
				res[line][pos++] = ' ';
			}
			res[line][pos++] = '\n';
			++line;
			pos = 0;
		}
		res[lines - 1][col - 1] = 0;
		cout << (char *)res;
	};
}
