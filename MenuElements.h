#pragma once
#include <string>
#include <iostream>

// "Resolve MenuElementContainer and Call. #Native #Reference"
#define RMEC_WRAP__NATIVE_REF(pretxt, posttxt) \
	switch (elementType) \
	{ \
	case TITLE: \
		pretxt((MenuElementTitle *)element)posttxt; \
		break; \
	case SUBTITLE: \
		pretxt((MenuElementSubtitle *)element)posttxt; \
		break; \
	case FUNCTION_BUTTON: \
		pretxt((MenuElementFunctionButton *)element)posttxt; \
		break; \
	case EDIT_FIELD: \
		pretxt((MenuElementEditField *)element)posttxt; \
		break; \
	}

// "Resolve MenuElementContainer and Call. #External #Reference"
#define RMEC_WRAP__EXTERN_REF(containerName, pretxt, posttxt) \
	MenuElementContainer::MenuElementType elementType = containerName->getType();\
	void* element = containerName -> getElement(); \
	switch (elementType) \
	{ \
	case MenuElementContainer::TITLE: \
		pretxt((MenuElementTitle *)element)posttxt; \
		break; \
	case MenuElementContainer::SUBTITLE: \
		pretxt((MenuElementSubtitle *)element)posttxt; \
		break; \
	case MenuElementContainer::FUNCTION_BUTTON: \
		pretxt((MenuElementFunctionButton *)element)posttxt; \
		break; \
	case MenuElementContainer::EDIT_FIELD: \
		pretxt((MenuElementEditField *)element)posttxt; \
		break; \
	}

#define NMEC_TITLE(...) menu->addElement(new MenuElementContainer(new MenuElementTitle(__VA_ARGS__)))
#define NMEC_SUBTITLE(...) menu->addElement(new MenuElementContainer(new MenuElementSubtitle(__VA_ARGS__)))
#define NMEC_FUNCTION_BUTTON(...) menu->addElement(new MenuElementContainer(new MenuElementFunctionButton(__VA_ARGS__)))
#define NMEC_EDIT_FIELD(...) menu->addElement(new MenuElementContainer(new MenuElementEditField(__VA_ARGS__)))

using namespace std;

class MenuElementContainer;
class MenuElementABC;
class MenuElementTitle;
class MenuElementSubtitle;
class MenuElementFunctionButton;
class MenuElementEditField;

class MenuElementContainer
{
public:
	enum MenuElementType
	{
		TITLE,
		SUBTITLE,
		FUNCTION_BUTTON,
		EDIT_FIELD
	};
private:
	MenuElementType elementType;
	void* element;
public:
	// Создание и разрушение
	MenuElementContainer(MenuElementTitle* ref) : elementType(TITLE), element(ref) {};
	MenuElementContainer(MenuElementSubtitle* ref) : elementType(SUBTITLE), element(ref) {};
	MenuElementContainer(MenuElementFunctionButton* ref) : elementType(FUNCTION_BUTTON), element(ref) {};
	MenuElementContainer(MenuElementEditField* ref) : elementType(EDIT_FIELD), element(ref) {};
	~MenuElementContainer() {};

	// Интерфейс
	void print() const;
	void recvCommand(int keyEvent);
	void* getElement() { return element; };
	MenuElementType getType() { return elementType; };
	void reset();
};

class MenuElementABC
{
protected:
	string text;
public:
	// Создание и разрушение
	MenuElementABC(string text) : text(text) {};
	~MenuElementABC() {};

	// Интерфейс
	virtual void print() const = 0;
	virtual void recvCommand(int keyEvent) = 0;
	virtual bool isChoosable() = 0;
	virtual void reset() = 0;
};

class MenuElementTitle : public MenuElementABC
{
public:
	// Создание и разрушение
	MenuElementTitle(string text) : MenuElementABC(text) {};
	~MenuElementTitle() {};

	// Интерфейс
	void print() const;
	void recvCommand(int keyEvent) {/*TODO: throw exception*/};
	bool isChoosable() { return false; };
	void reset() {};
};

class MenuElementSubtitle : public MenuElementABC
{
public:
	// Создание и разрушение
	MenuElementSubtitle(string text) : MenuElementABC(text) {};
	~MenuElementSubtitle() {};

	// Интерфейс
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
	// Создание и разрушение
	MenuElementFunctionButton(string text, void(*func)()) : MenuElementABC(text), func(func) {};
	~MenuElementFunctionButton() {};

	// Интерфейс
	void print() const;
	void recvCommand(int keyEvent);
	bool isChoosable() { return true; };
	void reset() {};
};

class MenuElementEditField : public MenuElementABC
{
	//  TODO: Реагирует только на клавиши, прописанные в векторе allowedCodes.
private:
	string input;
	bool isTextHidden;
public:
	// Создание и разрушение
	MenuElementEditField(string text, bool isTextHidden = false) : MenuElementABC(text), input(""), isTextHidden(isTextHidden) {};
	~MenuElementEditField() {};

	// Интерфейс
	void print() const;
	string getInput();
	void recvCommand(int keyEvent);
	bool isChoosable() { return true; };
	void reset() { input = ""; };
};
