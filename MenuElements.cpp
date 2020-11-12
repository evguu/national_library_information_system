#include "pch.h"
#include "MenuElements.h"
#include "Input.h"
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

string MenuElementChoice::str() const
{
	stringstream ss;
	int len = options.size();
	if (activeOption == 0)
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

bool MenuElementChoice::recvCommand(int keyEvent)
{
	switch (keyEvent)
	{
	case -KC_LEFT:
		if (activeOption != 0)
		{
			--activeOption;
		}
		return true;
	case -KC_RIGHT:
		if (activeOption + 1 < options.size())
		{
			++activeOption;
		}
		return true;
	}
	return false;
}
