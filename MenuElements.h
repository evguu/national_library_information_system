#pragma once
#include <string>
#include <iostream>

#define NMEC_TITLE(...) menu->addElement(new MenuElementTitle(__VA_ARGS__))
#define NMEC_SUBTITLE(...) menu->addElement(new MenuElementSubtitle(__VA_ARGS__))
#define NMEC_FUNCTION_BUTTON(...) menu->addElement(new MenuElementFunctionButton(__VA_ARGS__))
#define NMEC_EDIT_FIELD(...) menu->addElement(new MenuElementEditField(__VA_ARGS__))

using namespace std;

class MenuElementABC;
class MenuElementTitle;
class MenuElementSubtitle;
class MenuElementFunctionButton;
class MenuElementEditField;

class MenuElementABC
{
protected:
	string text;
public:
	// �������� � ����������
	MenuElementABC(string text) : text(text) {};
	virtual ~MenuElementABC() {};

	// ���������
	virtual void print() const = 0;
	virtual void recvCommand(int keyEvent) = 0;
	virtual bool isChoosable() = 0;
	virtual void reset() = 0;
};

class MenuElementTitle : public MenuElementABC
{
public:
	// �������� � ����������
	MenuElementTitle(string text) : MenuElementABC(text) {};
	~MenuElementTitle() {};

	// ���������
	void print() const;
	void recvCommand(int keyEvent) {/*TODO: throw exception*/};
	bool isChoosable() { return false; };
	void reset() {};
};

class MenuElementSubtitle : public MenuElementABC
{
public:
	// �������� � ����������
	MenuElementSubtitle(string text) : MenuElementABC(text) {};
	~MenuElementSubtitle() {};

	// ���������
	void print() const;
	void recvCommand(int keyEvent) {};
	bool isChoosable() { return false; };
	void reset() {};
};

class MenuElementFunctionButton : public MenuElementABC
{
private:
	void (*func)();
public:
	// �������� � ����������
	MenuElementFunctionButton(string text, void(*func)()) : MenuElementABC(text), func(func) {};
	~MenuElementFunctionButton() {};

	// ���������
	void print() const;
	void recvCommand(int keyEvent);
	bool isChoosable() { return true; };
	void reset() {};
};

class MenuElementEditField : public MenuElementABC
{
	//  TODO: ��������� ������ �� �������, ����������� � ������� allowedCodes.
private:
	string input;
	bool isTextHidden;
public:
	// �������� � ����������
	MenuElementEditField(string text, bool isTextHidden = false) : MenuElementABC(text), input(""), isTextHidden(isTextHidden) {};
	~MenuElementEditField() {};

	// ���������
	void print() const;
	string getInput();
	void recvCommand(int keyEvent);
	bool isChoosable() { return true; };
	void reset() { input = ""; };
};
