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

	NMEC_TITLE("Вход в систему");
	NMEC_SUBTITLE("Ввод данных");
	NMEC_EDIT_FIELD("Логин");
	NMEC_EDIT_FIELD("Пароль", true);
	NMEC_SUBTITLE("Навигация");
	NMEC_FUNCTION_BUTTON("Войти", []() {
		auto menuElements = Menu::getActive()->getElements();
		string login, password;
		auto it = menuElements.begin();
		it += 2;
		login = ((MenuElementEditField *)(*it))->getInput();
		it += 1;
		password = ((MenuElementEditField *)(*it))->getInput();
		// TODO: Здесь будут проверки данных
		// TODO: Функция сама сообщит об успешности входа.
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
	NMEC_FUNCTION_BUTTON("Назад", []() {
		loginMenu->reset();
		Menu::multiPopMenuStack(1);
	});

	loginMenu->initChosenElementIndex();
}

void initRegisterMenu()
{
	auto& menu = registerMenu;
	menu = new Menu();

	NMEC_TITLE("Регистрация");
	NMEC_SUBTITLE("Ввод данных");
	NMEC_EDIT_FIELD("Логин");
	NMEC_EDIT_FIELD("Пароль", true);
	NMEC_EDIT_FIELD("Повторите пароль", true);
	NMEC_SUBTITLE("Навигация");
	NMEC_FUNCTION_BUTTON("Зарегистрироваться", []() {
		auto menuElements = Menu::getActive()->getElements();
		string login, password, repeatPassword;
		auto it = menuElements.begin();
		it += 2;
		login = ((MenuElementEditField *)(*it))->getInput();
		it += 1;
		password = ((MenuElementEditField *)(*it))->getInput();
		it += 1;
		repeatPassword = ((MenuElementEditField *)(*it))->getInput();
		// TODO: Здесь будут проверки данных
		// TODO: Функция регистрации сама выводит сообщения пользователю.
		MainTypes::User::register_(login, password, repeatPassword);
		Menu::multiPopMenuStack(1);
	});
	NMEC_FUNCTION_BUTTON("Назад", []() {
		registerMenu->reset();
		Menu::multiPopMenuStack(1);
	});

	registerMenu->initChosenElementIndex();
}

void initUserMenu()
{
	auto& menu = userMenu;
	menu = new Menu();

	NMEC_TITLE("Меню пользователя");
	NMEC_SUBTITLE("Работа с данными");
	NMEC_FUNCTION_BUTTON("Обзор данных", []() {});
	NMEC_FUNCTION_BUTTON("Изменение данных", []() {});
	NMEC_SUBTITLE("Основные функции");
	NMEC_FUNCTION_BUTTON("Выдать книгу", []() {});
	NMEC_SUBTITLE("Навигация");
	NMEC_FUNCTION_BUTTON("Назад", []() {
		userMenu->reset();
		Menu::multiPopMenuStack(1);
	});

	userMenu->initChosenElementIndex();
}

void initAdminMenu()
{
	auto& menu = adminMenu;
	menu = new Menu();

	NMEC_TITLE("Меню администратора");
	NMEC_SUBTITLE("Работа с пользователями");
	NMEC_FUNCTION_BUTTON("Блокировка пользователей", []() {});
	NMEC_FUNCTION_BUTTON("Отчеты о данных", []() {});
	NMEC_SUBTITLE("Навигация");
	NMEC_FUNCTION_BUTTON("Назад", []() {
		adminMenu->reset();
		Menu::multiPopMenuStack(1);
	});

	adminMenu->initChosenElementIndex();
}

void initStartMenu()
{
	auto& menu = startMenu;
	menu = new Menu();

	NMEC_TITLE("Информационная система национальной библиотеки");
	NMEC_SUBTITLE("Авторизация");
	NMEC_FUNCTION_BUTTON("Войти", []() {loginMenu->addToStack(); });
	NMEC_FUNCTION_BUTTON("Зарегистрироваться", []() {registerMenu->addToStack(); });
	NMEC_SUBTITLE("Навигация");
	NMEC_FUNCTION_BUTTON("Выйти из программы", []() {isLoopRunning = false; });

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