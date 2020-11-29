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

const string MenuElementChoice::noChoicesFoundMessage = "RESERVED_TEXT::asdqe021-24789102-12kutaas-flkaput-rand1024-NO_CHOICES_FOUND";

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
	else
	{
		ss << "  " << text << ": <-" << options[activeOption] << "->" << endl;
	}
	return ss.str();
}

clock_t _lastClock = 0;
bool _wasPreviousDirectionRight = false;
int _timeCounter = 0;
const int _maximalComboInterval = 200;
const int _maxTrueSpeed = 64;
const int _doublingTime = 3000;

bool MenuElementChoice::recvCommand(int keyEvent)
{
	switch (keyEvent)
	{
		case -KC_LEFT:
		{
			if (options.size() > 1)
			{
				int timeElapsed = (long)(((double)clock() - _lastClock) / CLOCKS_PER_SEC * 1000);
				if ((timeElapsed < _maximalComboInterval) && !_wasPreviousDirectionRight)
				{
					_timeCounter += timeElapsed;
				}
				else
				{
					_timeCounter = 0;
					_wasPreviousDirectionRight = false;
				}
				int trueSpeed = 1 << (2 * _timeCounter / _doublingTime);
				if (trueSpeed > _maxTrueSpeed)
				{
					trueSpeed = _maxTrueSpeed;
				}
				activeOption = (options.size() - trueSpeed + activeOption) % options.size();
			}
			_lastClock = clock();
			return true;
		}
		case -KC_RIGHT:
		{
			if (options.size() > 1)
			{
				int timeElapsed = (long)(((double)clock() - _lastClock) / CLOCKS_PER_SEC * 1000);
				if ((timeElapsed < _maximalComboInterval) && _wasPreviousDirectionRight)
				{
					_timeCounter += timeElapsed;
				}
				else
				{
					_timeCounter = 0;
					_wasPreviousDirectionRight = true;
				}
				int trueSpeed = 1 << (2 * _timeCounter / _doublingTime);
				if (trueSpeed > _maxTrueSpeed)
				{
					trueSpeed = _maxTrueSpeed;
				}
				activeOption = (options.size() + trueSpeed + activeOption) % options.size();
			}
			_lastClock = clock();
			return true;
		}
	}
	return false;
}
