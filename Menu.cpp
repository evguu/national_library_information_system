#include "pch.h"
#include <cassert>
#include "Input.h"
#include "Menu.h"

stack<Menu *> Menu::menuStack = stack<Menu *>();

void Menu::print() const
{
	// Меню не может быть пустым
	assert(elements.size());

	// В меню должен быть выбран элемент
	assert((chosenElementIndex != -1));

	// Суть проста: пройтись по всем элементам меню и вызвать для них метод печати.
	// Но есть загвоздка: именно этот метод должен показывать, какой именно элемент выбран.
	// Для этого здесь ведется подсчет индекса выводимого элемента.
	// Если он равен индексу активного элемента меню, обозначить его активность выбранным методом.
	int index = 0;
	bool tmp;
	for (const auto& it : elements)
	{
		RMEC_WRAP__EXTERN_REF(it,tmp=,->isChoosable());
		if (tmp)
		{
			if (chosenElementIndex == index)
			{
				cout << ">>";
			}
			else
			{
				cout << " +";
			}
		}
		it->print();
		++index;
	}
}

void Menu::recvCommand(int keyEvent)
{
	int index;
	bool tmp;
	vector<MenuElementContainer *>::iterator lim;
	switch (keyEvent)
	{
	case -KC_DOWN:
		index = chosenElementIndex + 1;
		lim = elements.end();
		for (auto it = elements.begin() + chosenElementIndex + 1; it != lim; ++it)
		{
			RMEC_WRAP__EXTERN_REF((*it), tmp=, ->isChoosable());
			if (tmp)
			{
				chosenElementIndex = index;
				return;
			}
			++index;
		}
		break;
	case -KC_UP:
		index = 0;
		lim = elements.begin() + chosenElementIndex;
		for (auto it = elements.begin(); it != lim; ++it)
		{
			RMEC_WRAP__EXTERN_REF((*it), tmp=, ->isChoosable());
			if (tmp)
			{
				chosenElementIndex = index;
			}
			++index;
		}
		break;
	default:
		(*(elements.begin() + chosenElementIndex))->recvCommand(keyEvent);
	}
}

void Menu::addElement(MenuElementContainer * ref)
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
		RMEC_WRAP__EXTERN_REF(it,tmp=,->isChoosable());
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
	menuStack.top()->print();
}

void Menu::multiPopMenuStack(int popCount)
{
	for (int i = 0; i < popCount; ++i)
	{
		menuStack.pop();
	}
}
