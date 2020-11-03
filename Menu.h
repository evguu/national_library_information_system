#pragma once
#include <stack>
#include <vector>
#include "MenuElements.h"
using namespace std;

class Menu;

class Menu
{
private:
	static stack<Menu *> menuStack;
	vector<MenuElementContainer *> elements;
	int chosenElementIndex;
public:
	// Создание и разрушение
	Menu() : chosenElementIndex(-1) {};
	~Menu()
	{
		for (auto it:elements)
		{ 
			// TODO:
		}
	};

	// Интерфейс
	void print() const;
	void recvCommand(int keyEvent);
	void addElement(MenuElementContainer* ref);
	void addToStack();
	auto& getElements() { return elements; }
	void initChosenElementIndex();
	int getChosenElementIndex() { return chosenElementIndex; };
	void reset();

	// Статический интерфейс
	static void printActive();
	static Menu* getActive() { return menuStack.top(); };
	static void multiPopMenuStack(int popCount = 1);
};
