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
	vector<MenuElement *> elements;
	int chosenElementIndex;
public:
	// Создание и разрушение
	Menu() : chosenElementIndex(-1) {};
	~Menu()
	{
		for (auto it:elements)
		{ 
			delete it;
		}
	};

	// Интерфейс
	string str() const;
	bool recvCommand(int keyEvent);
	void addElement(MenuElement* ref);
	void addToStack();
	auto& getElements() { return elements; }
	void initChosenElementIndex();
	int getChosenElementIndex() { return chosenElementIndex; };
	void reset();

	// Статический интерфейс
	static Menu* getActive() { return menuStack.top(); };
	static void multiPopMenuStack(int popCount = 1);
};
