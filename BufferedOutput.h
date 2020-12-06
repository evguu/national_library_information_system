#pragma once
#include <iostream>
#include <string>
using namespace std;

void noBlinkOutput(string src)
{
	const int len = 127;
	const int col = 40;
	char res[col][len+1];
	int line = 0;
	int pos = 0;
	for (auto i : src)
	{
		if (i == '\n')
		{
			while(pos != len)
			{
				res[line][pos++] = ' ';
			}
			res[line][pos++] = '\n';
			++line;
			pos = 0;
		}
		else
		{
			if (pos < len)
			{
				res[line][pos++] = i;
			}
			else
			{
				res[line][len-3] = '.';
				res[line][len-2] = '.';
				res[line][len-1] = '.';
				res[line][len] = '\n';
				++line;
				pos = 0;
			}
		}
	}
	while (line < col)
	{
		while (pos != len)
		{
			res[line][pos++] = ' ';
		}
		res[line][pos++] = '\n';
		++line;
		pos = 0;
	}
	res[col-1][len] = 0;
	cout << (char *)res;
};