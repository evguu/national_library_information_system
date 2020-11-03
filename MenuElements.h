#pragma once
#include <string>
#include <iostream>

#define NMEC_TITLE(...) menu->addElement(new MenuElementTitle(__VA_ARGS__))
#define NMEC_SUBTITLE(...) menu->addElement(new MenuElementSubtitle(__VA_ARGS__))
#define NMEC_FUNCTION_BUTTON(...) menu->addElement(new MenuElementFunctionButton(__VA_ARGS__))
#define NMEC_EDIT_FIELD(...) menu->addElement(new MenuElementEditField(__VA_ARGS__))

using namespace std;

class MenuElement;
class MenuElementTitle;
class MenuElementSubtitle;
class MenuElementFunctionButton;
class MenuElementEditField;

class MenuElement
{
protected:
	string text;
public:
	// �������� � ����������
	MenuElement(string text) : text(text) {};
	virtual ~MenuElement() {};

	// ���������
	virtual void print() const = 0;
	virtual void recvCommand(int keyEvent) = 0;
	virtual bool isChoosable() = 0;
	virtual void reset() = 0;
};

class MenuElementTitle : public MenuElement
{
public:
	// �������� � ����������
	MenuElementTitle(string text) : MenuElement(text) {};
	~MenuElementTitle() {};

	// ���������
	void print() const;
	void recvCommand(int keyEvent) {/*TODO: throw exception*/};
	bool isChoosable() { return false; };
	void reset() {};
};

class MenuElementSubtitle : public MenuElement
{
public:
	// �������� � ����������
	MenuElementSubtitle(string text) : MenuElement(text) {};
	~MenuElementSubtitle() {};

	// ���������
	void print() const;
	void recvCommand(int keyEvent) {};
	bool isChoosable() { return false; };
	void reset() {};
};

class MenuElementFunctionButton : public MenuElement
{
private:
	void (*func)();
public:
	// �������� � ����������
	MenuElementFunctionButton(string text, void(*func)()) : MenuElement(text), func(func) {};
	~MenuElementFunctionButton() {};

	// ���������
	void print() const;
	void recvCommand(int keyEvent);
	bool isChoosable() { return true; };
	void reset() {};
};

class MenuElementEditField : public MenuElement
{
	//  TODO: ��������� ������ �� �������, ����������� � ������� allowedCodes.
private:
	string input;
	bool isTextHidden;
public:
	// �������� � ����������
	MenuElementEditField(string text, bool isTextHidden = false) : MenuElement(text), input(""), isTextHidden(isTextHidden) {};
	~MenuElementEditField() {};

	// ���������
	void print() const;
	string getInput();
	void recvCommand(int keyEvent);
	bool isChoosable() { return true; };
	void reset() { input = ""; };
};
