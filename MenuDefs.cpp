#include "pch.h"
#include "MenuDefs.h"
#include "Menu.h"
#include "MenuElements.h"
#include "User.h"
#include "Input.h"
#include <Windows.h>
#include <mutex>
using namespace std;

Menu* loginMenu;
Menu* registerMenu;
Menu* userMenu;
Menu* adminMenu;
Menu* startMenu;
bool isLoopRunning = true;
clock_t lastKeyPressTime = -1;
mutex g_lock;
long elapsed;

void initLoginMenu()
{
	auto& menu = loginMenu;
	menu = new Menu();

	NME_TITLE("���� � �������");
	NME_SUBTITLE("���� ������");
	NME_EDIT_FIELD("�����");
	NME_EDIT_FIELD("������", true);
	NME_SUBTITLE("���������");
	NME_FUNC_BUTTON("�����", []() {
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
	NME_FUNC_BUTTON("�����", []() {
		loginMenu->reset();
		Menu::multiPopMenuStack(1);
	});

	loginMenu->initChosenElementIndex();
}

void initRegisterMenu()
{
	auto& menu = registerMenu;
	menu = new Menu();

	NME_TITLE("�����������");
	NME_SUBTITLE("���� ������");
	NME_EDIT_FIELD("�����");
	NME_EDIT_FIELD("������", true);
	NME_EDIT_FIELD("��������� ������", true);
	NME_SUBTITLE("���������");
	NME_FUNC_BUTTON("������������������", []() {
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
	NME_FUNC_BUTTON("�����", []() {
		registerMenu->reset();
		Menu::multiPopMenuStack(1);
	});

	registerMenu->initChosenElementIndex();
}

void initUserMenu()
{
	auto& menu = userMenu;
	menu = new Menu();

	NME_TITLE("���� ������������");
	NME_SUBTITLE("������ � �������");
	NME_FUNC_BUTTON("����� ������", []() {});
	NME_FUNC_BUTTON("��������� ������", []() {});
	NME_SUBTITLE("�������� �������");
	NME_FUNC_BUTTON("������ �����", []() {});
	NME_SUBTITLE("���������");
	NME_FUNC_BUTTON("�����", []() {
		userMenu->reset();
		Menu::multiPopMenuStack(1);
	});

	userMenu->initChosenElementIndex();
}

void initAdminMenu()
{
	auto& menu = adminMenu;
	menu = new Menu();

	NME_TITLE("���� ��������������");
	NME_SUBTITLE("������ � ��������������");
	NME_FUNC_BUTTON("���������� �������������", []() {});
	NME_FUNC_BUTTON("������ � ������", []() {});
	NME_SUBTITLE("���������");
	NME_FUNC_BUTTON("�����", []() {
		adminMenu->reset();
		Menu::multiPopMenuStack(1);
	});

	adminMenu->initChosenElementIndex();
}

void initStartMenu()
{
	auto& menu = startMenu;
	menu = new Menu();

	NME_TITLE("�������������� ������� ������������ ����������");
	NME_SUBTITLE("�����������");
	NME_FUNC_BUTTON("�����", []() {loginMenu->addToStack(); });
	NME_FUNC_BUTTON("������������������", []() {registerMenu->addToStack(); });
	NME_SUBTITLE("���������");
	NME_FUNC_BUTTON("����� �� ���������", []() {isLoopRunning = false; });

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
		bool hasReacted = Menu::getActive()->recvCommand(keyEvent);
		if (hasReacted)
		{
			g_lock.lock();
			lastKeyPressTime = clock();
			g_lock.unlock();
		}
	}
}

void menuPrintLoop()
{
	while (isLoopRunning)
	{
		g_lock.lock();
		if (clock() - lastKeyPressTime < 200 || lastKeyPressTime == -1)
		{
			if (lastKeyPressTime == -1)
			{
				lastKeyPressTime = 0;
			}
			system("cls");
			cout << endl;
			Menu::printActive();
			cout << endl << endl << endl;
		}
		g_lock.unlock();
		Sleep(100);
	}
}