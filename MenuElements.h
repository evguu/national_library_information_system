#pragma once
#include <string>
#include <vector>
#include <iostream>

#define NME_TITLE(...) menu->addElement(new MenuElementTitle(__VA_ARGS__))
#define NME_SUBTITLE(...) menu->addElement(new MenuElementSubtitle(__VA_ARGS__))
#define NME_FUNC_BUTTON(...) menu->addElement(new MenuElementFunctionButton(__VA_ARGS__))
#define NME_EDIT_FIELD(...) menu->addElement(new MenuElementEditField(__VA_ARGS__))
#define NME_CHOICE(...) menu->addElement(new MenuElementChoice(__VA_ARGS__))
#define MI_START(x) auto& menu = x; if (menu) { delete menu; }; menu = new Menu();
#define MI_END menu->initChosenElementIndex();

using namespace std;

class MenuElement;
class MenuElementTitle;
class MenuElementSubtitle;
class MenuElementFunctionButton;
class MenuElementEditField;
class MenuElementChoice;

class MenuElement
{
protected:
	string text;
public:
	// Создание и разрушение
	MenuElement(string text) : text(text) {};
	virtual ~MenuElement() {};

	// Интерфейс
	virtual string str() const = 0;
	virtual bool recvCommand(int keyEvent) = 0;
	virtual bool isChoosable() = 0;
	virtual void reset() = 0;
};

class MenuElementTitle : public MenuElement
{
public:
	// Создание и разрушение
	MenuElementTitle(string text) : MenuElement(text) {};
	~MenuElementTitle() {};

	// Интерфейс
	string str() const;
	bool recvCommand(int keyEvent) { return false; };
	bool isChoosable() { return false; };
	void reset() {};
};

class MenuElementSubtitle : public MenuElement
{
public:
	// Создание и разрушение
	MenuElementSubtitle(string text) : MenuElement(text) {};
	~MenuElementSubtitle() {};

	// Интерфейс
	string str() const;
	bool recvCommand(int keyEvent) { return false; };
	bool isChoosable() { return false; };
	void reset() {};
};

class MenuElementFunctionButton : public MenuElement
{
private:
	void (*func)();
public:
	// Создание и разрушение
	MenuElementFunctionButton(string text, void(*func)()) : MenuElement(text), func(func) {};
	~MenuElementFunctionButton() {};

	// Интерфейс
	string str() const;
	bool recvCommand(int keyEvent);
	bool isChoosable() { return true; };
	void reset() {};
};

class MenuElementEditField : public MenuElement
{
private:
	string input;
	bool isTextHidden;
	string allowedSymbols;
	int maxLength;
public:
	// Создание и разрушение
	MenuElementEditField(string text, bool isTextHidden = false, string allowedSymbols = "", int maxLength = 0):
		MenuElement(text), input(""), isTextHidden(isTextHidden), allowedSymbols(allowedSymbols), maxLength(maxLength) {};
	~MenuElementEditField() {};

	// Интерфейс
	string str() const;
	string getInput();
	bool recvCommand(int keyEvent);
	bool isChoosable() { return true; };
	void reset() { input = ""; };
};

class MenuElementChoice : public MenuElement
{
private:
	vector<string> options;
	int activeOption = 0;
public:
	MenuElementChoice(string text, vector<string> options) : MenuElement(text), options(options) {};
	~MenuElementChoice() {};

	string str() const;
	string getChoice() { return options[activeOption]; };
	bool recvCommand(int keyEvent);
	bool isChoosable() { return true; };
	void reset() { activeOption = 0; };
};