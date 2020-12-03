#pragma once
#include <stack>
#include <vector>
#include <mutex>
#include "MenuElements.h"
using namespace std;

class Menu;

class Menu
{
private:
	static stack<Menu *> menuStack;
	static bool isLoopRunning;
	static bool hasMenuChanged;
	static mutex g_lock;
	static const int viewField;
	vector<MenuElement *> elements;
	int chosenElementIndex;
	static void controlLoop();
	static void printLoop();
public:
	Menu() : chosenElementIndex(-1) {};
	~Menu()
	{
		for (auto it:elements)
		{ 
			delete it;
		}
	};
	string str() const;
	bool recvCommand(int keyEvent);
	void addElement(MenuElement* ref);
	void addToStack();
	auto& getElements() { return elements; }
	void initChosenElementIndex();
	int getChosenElementIndex() { return chosenElementIndex; };
	void reset();
	static Menu* getActive() { return menuStack.top(); };
	static void multiPopMenuStack(int popCount = 1);
	static void run()
	{
		thread t1(controlLoop);
		thread t2(printLoop);
		t1.join();
		t2.join();
	}
	static void finish() { isLoopRunning = false; };
	static auto& getMutex() { return g_lock; };
};
