#include "pch.h"
#include "MenuElements.h"
#include "Input.h"

void MenuElementTitle::print() const
{
	cout << "-< " << text << " >- " << endl;
}

void MenuElementSubtitle::print() const
{
	cout << endl << "      [ " << text << " ]" << endl;
}

void MenuElementFunctionButton::print() const
{
	cout << "  " << text << endl;
}

void MenuElementFunctionButton::recvCommand(int keyEvent)
{
	switch (keyEvent)
	{
	case -KC_ENTER:
		func();
		break;
	}
}

void MenuElementEditField::print() const
{
	if (isTextHidden)
	{
		cout << "  " << text << ": ";
		for (int i = 0; i < (int)input.length(); i++)
		{
			cout << "*";
		}
		cout << endl;
	}
	else
	{
		cout << "  " << text << ": " << input << endl;
	}
}

string MenuElementEditField::getInput()
{
	return input;
}

void MenuElementEditField::recvCommand(int keyEvent)
{
	if (keyEvent > 0)
	{
		input += (char)keyEvent;
		return;
	}
	if (keyEvent == -KC_DELETE || keyEvent == -KC_BACKSPACE)
	{
		if(input.length()) input.pop_back();
	}
}
