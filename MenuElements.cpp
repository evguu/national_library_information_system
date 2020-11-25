#include "pch.h"
#include "MenuElements.h"
#include "Input.h"
#include <ctime>
#include <sstream>

string MenuElementTitle::str() const
{
	stringstream ss;
	ss << "-< " << text << " >- " << endl;
	return ss.str();
}

string MenuElementSubtitle::str() const
{
	stringstream ss;
	ss << endl << "      [ " << text << " ]" << endl;
	return ss.str();
}

string MenuElementFunctionButton::str() const
{
	stringstream ss;
	ss << "  " << text << endl;
	return ss.str();
}

bool MenuElementFunctionButton::recvCommand(int keyEvent)
{
	switch (keyEvent)
	{
	case -KC_ENTER:
		func();
		return true;
	}
	return false;
}

string MenuElementEditField::str() const
{
	stringstream ss;
	if (isTextHidden)
	{
		ss << "  " << text << ": ";
		for (int i = 0; i < (int)input.length(); i++)
		{
			ss << "*";
		}
		ss << endl;
	}
	else
	{
		ss << "  " << text << ": " << input << endl;
	}
	return ss.str();
}

string MenuElementEditField::getInput()
{
	return input;
}

bool MenuElementEditField::recvCommand(int keyEvent)
{
	if (keyEvent > 0)
	{
		if (((allowedSymbols.length() == 0) || (allowedSymbols.find((char)keyEvent) != string::npos)) && ((maxLength == 0) || (input.length() < maxLength)))
		{
			input += (char)keyEvent;
			return true;
		}
	}
	if (keyEvent == -KC_DELETE || keyEvent == -KC_BACKSPACE)
	{
		if(input.length()) input.pop_back();
		return true;
	}
	return false;
}

const string MenuElementChoice::noChoicesFoundMessage = "RESERVED_TEXT::asdqe021-24789102-12kutaas-flkaput-rand1024-EMPTY_VECTOR";

string MenuElementChoice::str() const
{
	stringstream ss;
	int len = options.size();
	if (len == 0)
	{
		ss << "  " << text << ": -- ÑÏÈÑÎÊ ÂÛÁÎÐÀ ÏÓÑÒ! --" << endl;
	}
	else if (len == 1)
	{
		ss << "  " << text << ": --" << options[activeOption] << "--" << endl;
	}
	else if (activeOption == 0)
	{
		ss << "  " << text << ": --" << options[activeOption] << "->" << endl;
	}
	else if (len == activeOption + 1)
	{
		ss << "  " << text << ": <-" << options[activeOption] << "--" << endl;
	}
	else
	{
		ss << "  " << text << ": <-" << options[activeOption] << "->" << endl;
	}
	return ss.str();
}

clock_t _lastClock = 0;
bool _wasPreviousDirectionRight = false;
int _speedCounter = 0;
const int _speedCutFactor = 5;
const int _maxTrueSpeed = 50;
const int _maximalComboInterval = 200;

bool MenuElementChoice::recvCommand(int keyEvent)
{
	switch (keyEvent)
	{
		case -KC_LEFT:
		{
			if (activeOption != 0)
			{
				if (((long)(((double)clock() - _lastClock) / CLOCKS_PER_SEC * 1000) < _maximalComboInterval) && !_wasPreviousDirectionRight)
				{
					_speedCounter++;
				}
				else
				{
					_speedCounter = 0;
					_wasPreviousDirectionRight = false;
				}
				int trueSpeed = 1 + (int)(_speedCounter / _speedCutFactor);
				if (trueSpeed > _maxTrueSpeed)
				{
					trueSpeed = _maxTrueSpeed;
				}
				if (trueSpeed > activeOption)
				{
					trueSpeed = activeOption;
				}
				activeOption -= trueSpeed;
			}
			_lastClock = clock();
			return true;
		}
		case -KC_RIGHT:
		{
			if (activeOption + 1 < options.size())
			{
				if (((long)(((double)clock() - _lastClock) / CLOCKS_PER_SEC * 1000) < _maximalComboInterval) && _wasPreviousDirectionRight)
				{
					_speedCounter++;
				}
				else
				{
					_speedCounter = 0;
					_wasPreviousDirectionRight = true;
				}
				int trueSpeed = 1 + (int)(_speedCounter / _speedCutFactor);
				if (trueSpeed > _maxTrueSpeed)
				{
					trueSpeed = _maxTrueSpeed;
				}
				if (trueSpeed > options.size() - activeOption - 1)
				{
					trueSpeed = options.size() - activeOption - 1;
				}
				activeOption += trueSpeed;
			}
			_lastClock = clock();
			return true;
		}
	}
	return false;
}
