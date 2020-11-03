#include "pch.h"
#include "MenuDefs.h"
#include "Menu.h"
#include "MenuElements.h"
#include "User.h"
#include "Input.h"
#include <Windows.h>
using namespace std;

Menu* loginMenu;
Menu* registerMenu;
Menu* userMenu;
Menu* adminMenu;
Menu* startMenu;
bool isLoopRunning = true;

void initLoginMenu()
{
	auto& menu = loginMenu;
	menu = new Menu();

	NMEC_TITLE("���� � �������");
	NMEC_SUBTITLE("���� ������");
	NMEC_EDIT_FIELD("�����");
	NMEC_EDIT_FIELD("������", true);
	NMEC_SUBTITLE("���������");
	NMEC_FUNCTION_BUTTON("�����", []() {
		auto menuElements = Menu::getActive()->getElements();
		string login, password;
		auto it = menuElements.begin();
		it += 2;
		login = ((MenuElementEditField *)(*it))->getInput();
		it += 1;
		password = ((MenuElementEditField *)(*it))->getInput();
		// TODO: ����� ����� �������� ������
		// TODO: ������� ���� ������� �� ���������� �����.
		MainTypes::User::login_(login, password);
		if (MainTypes::User::getActive())
		{
			Menu::multiPopMenuStack(1);
			if (MainTypes::User::getActive()->getIsAdmin())
			{
				adminMenu->addToStack();
			}
			else
			{
				userMenu->addToStack();
			}
		}
	});
	NMEC_FUNCTION_BUTTON("�����", []() {
		loginMenu->reset();
		Menu::multiPopMenuStack(1);
	});

	loginMenu->initChosenElementIndex();
}

void initRegisterMenu()
{
	auto& menu = registerMenu;
	menu = new Menu();

	NMEC_TITLE("�����������");
	NMEC_SUBTITLE("���� ������");
	NMEC_EDIT_FIELD("�����");
	NMEC_EDIT_FIELD("������", true);
	NMEC_EDIT_FIELD("��������� ������", true);
	NMEC_SUBTITLE("���������");
	NMEC_FUNCTION_BUTTON("������������������", []() {
		auto menuElements = Menu::getActive()->getElements();
		string login, password, repeatPassword;
		auto it = menuElements.begin();
		it += 2;
		login = ((MenuElementEditField *)(*it))->getInput();
		it += 1;
		password = ((MenuElementEditField *)(*it))->getInput();
		it += 1;
		repeatPassword = ((MenuElementEditField *)(*it))->getInput();
		// TODO: ����� ����� �������� ������
		// TODO: ������� ����������� ���� ������� ��������� ������������.
		MainTypes::User::register_(login, password, repeatPassword);
		Menu::multiPopMenuStack(1);
	});
	NMEC_FUNCTION_BUTTON("�����", []() {
		registerMenu->reset();
		Menu::multiPopMenuStack(1);
	});

	registerMenu->initChosenElementIndex();
}

void initUserMenu()
{
	auto& menu = userMenu;
	menu = new Menu();

	NMEC_TITLE("���� ������������");
	NMEC_SUBTITLE("������ � �������");
	NMEC_FUNCTION_BUTTON("����� ������", []() {});
	NMEC_FUNCTION_BUTTON("��������� ������", []() {});
	NMEC_SUBTITLE("�������� �������");
	NMEC_FUNCTION_BUTTON("������ �����", []() {});
	NMEC_SUBTITLE("���������");
	NMEC_FUNCTION_BUTTON("�����", []() {
		userMenu->reset();
		Menu::multiPopMenuStack(1);
	});

	userMenu->initChosenElementIndex();
}

void initAdminMenu()
{
	auto& menu = adminMenu;
	menu = new Menu();

	NMEC_TITLE("���� ��������������");
	NMEC_SUBTITLE("������ � ��������������");
	NMEC_FUNCTION_BUTTON("���������� �������������", []() {});
	NMEC_FUNCTION_BUTTON("������ � ������", []() {});
	NMEC_SUBTITLE("���������");
	NMEC_FUNCTION_BUTTON("�����", []() {
		adminMenu->reset();
		Menu::multiPopMenuStack(1);
	});

	adminMenu->initChosenElementIndex();
}

void initStartMenu()
{
	auto& menu = startMenu;
	menu = new Menu();

	NMEC_TITLE("�������������� ������� ������������ ����������");
	NMEC_SUBTITLE("�����������");
	NMEC_FUNCTION_BUTTON("�����", []() {loginMenu->addToStack(); });
	NMEC_FUNCTION_BUTTON("������������������", []() {registerMenu->addToStack(); });
	NMEC_SUBTITLE("���������");
	NMEC_FUNCTION_BUTTON("����� �� ���������", []() {isLoopRunning = false; });

	startMenu->initChosenElementIndex();
}

void menuInitAll()
{
	initLoginMenu();
	initRegisterMenu();
	initAdminMenu();
	initUserMenu();
	initStartMenu();
	startMenu->addToStack();
}

void menuControlLoop()
{
	int keyEvent;
	while (isLoopRunning)
	{
		keyEvent = Utils::inputKeyEvent();
		Menu::getActive()->recvCommand(keyEvent);
	}
}

void menuPrintLoop()
{
	while (isLoopRunning)
	{
		system("cls");
		cout << endl;
		Menu::printActive();
		cout << endl << endl << endl;
		Sleep(100);
	}
}