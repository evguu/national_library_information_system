#include "pch.h"
#include <cassert>
#include "Input.h"
#include <sstream>
#include "Menu.h"

stack<Menu *> Menu::menuStack = stack<Menu *>();

string Menu::str() const
{
	assert(elements.size()); // Меню пустое
	assert((chosenElementIndex != -1)); // Активный элемент не установлен

	stringstream ss;

	int index = 0;
	bool tmp;
	for (const auto& it : elements)
	{
		tmp = it->isChoosable();
		if (tmp)
		{
			if (chosenElementIndex == index)
			{
				ss << ">>";
			}
			else
			{
				ss << " +";
			}
		}
		ss << it->str();//FIXME
		++index;
	}
	return ss.str();
}

bool Menu::recvCommand(int keyEvent)
{
	int index;
	bool tmp;
	vector<MenuElement *>::iterator lim;
	switch (keyEvent)
	{
	case -KC_DOWN:
		index = chosenElementIndex + 1;
		lim = elements.end();
		for (auto it = elements.begin() + chosenElementIndex + 1; it != lim; ++it)
		{
			tmp= (*it)->isChoosable();
			if (tmp)
			{
				chosenElementIndex = index;
				return true;
			}
			++index;
		}
		return true;
	case -KC_UP:
		index = 0;
		lim = elements.begin() + chosenElementIndex;
		for (auto it = elements.begin(); it != lim; ++it)
		{
			tmp= (*it)->isChoosable();
			if (tmp)
			{
				chosenElementIndex = index;
			}
			++index;
		}
		return true;
	default:
		return (*(elements.begin() + chosenElementIndex))->recvCommand(keyEvent);
	}
}

void Menu::addElement(MenuElement * ref)
{
	elements.push_back(ref);
}

void Menu::addToStack()
{
	menuStack.push(this);
}

void Menu::initChosenElementIndex()
{
	int index = 0;
	bool tmp;
	for (const auto& it : elements)
	{
		tmp= it->isChoosable();
		if (tmp)
		{
			chosenElementIndex = index;
			return;
		}
		++index;
	}
	chosenElementIndex = -1;
}

void Menu::reset()
{
	for (const auto& it : elements)
	{
		it->reset();
	}
	initChosenElementIndex();
}

void Menu::printActive()
{
	cout << menuStack.top()->str();
}

void Menu::multiPopMenuStack(int popCount)
{
	for (int i = 0; i < popCount; ++i)
	{
		menuStack.pop();
	}
}
