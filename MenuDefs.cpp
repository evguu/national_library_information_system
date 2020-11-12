#include "pch.h"
#include "MenuDefs.h"
#include "Menu.h"
#include "MenuElements.h"
#include "User.h"
#include "Input.h"
#include <Windows.h>
#include <mutex>
using namespace std;

Menu* loginMenu = nullptr;
Menu* registerMenu = nullptr;
Menu* userMenu = nullptr;
Menu* adminMenu = nullptr;
Menu* startMenu = nullptr;
Menu* dataTypeMenu = nullptr;
Menu* registerConfirmationMenu = nullptr;

bool isLoopRunning = true;
bool hasMenuChanged = true;
mutex g_lock;
long elapsed;

void initLoginMenu()
{
	auto& menu = loginMenu;
	if (menu) { delete menu; };
	menu = new Menu();

	NME_TITLE("Вход в систему");
	NME_SUBTITLE("Ввод данных");
	NME_EDIT_FIELD("Логин", false, Constraints::User::LOGIN_ALLOWED_CHARS, Constraints::User::LOGIN_MAX_LENGTH);
	NME_EDIT_FIELD("Пароль", true, Constraints::User::PASSWORD_ALLOWED_CHARS, Constraints::User::PASSWORD_MAX_LENGTH);
	NME_SUBTITLE("Навигация");
	NME_FUNC_BUTTON("Войти", []() {
		auto menuElements = Menu::getActive()->getElements();
		string login, password;
		auto it = menuElements.begin();
		it += 2;
		login = ((MenuElementEditField *)(*it))->getInput();
		it += 1;
		password = ((MenuElementEditField *)(*it))->getInput();
		User::loginUser(login, password);
		if (User::getActiveUser())
		{
			loginMenu->reset();
			Menu::multiPopMenuStack(1);
			if (User::getActiveUser()->getIsAdmin())
			{
				adminMenu->addToStack();
			}
			else
			{
				userMenu->addToStack();
			}
		}
	});
	NME_FUNC_BUTTON("Назад", []() {
		loginMenu->reset();
		Menu::multiPopMenuStack(1);
	});

	loginMenu->initChosenElementIndex();
}

void initRegisterMenu()
{
	auto& menu = registerMenu;
	if (menu) { delete menu; };
	menu = new Menu();

	NME_TITLE("Регистрация");
	NME_SUBTITLE("Ввод данных");
	NME_EDIT_FIELD("ФИО", false, Constraints::Person::FULL_NAME_ALLOWED_CHARS, Constraints::Person::FULL_NAME_MAX_LENGTH);
	NME_EDIT_FIELD("Логин", false, Constraints::User::LOGIN_ALLOWED_CHARS, Constraints::User::LOGIN_MAX_LENGTH);
	NME_EDIT_FIELD("Пароль", true, Constraints::User::PASSWORD_ALLOWED_CHARS, Constraints::User::PASSWORD_MAX_LENGTH);
	NME_EDIT_FIELD("Повторите пароль", true, Constraints::User::PASSWORD_ALLOWED_CHARS, Constraints::User::PASSWORD_MAX_LENGTH);
	NME_SUBTITLE("Навигация");
	NME_FUNC_BUTTON("Зарегистрироваться", []() {
		auto menuElements = Menu::getActive()->getElements();
		string fullName, login, password, repeatPassword;
		auto it = menuElements.begin();
		it += 2;
		fullName = ((MenuElementEditField *)(*it))->getInput();
		it += 1;
		login = ((MenuElementEditField *)(*it))->getInput();
		it += 1;
		password = ((MenuElementEditField *)(*it))->getInput();
		it += 1;
		repeatPassword = ((MenuElementEditField *)(*it))->getInput();
		if (User::registerUser(fullName, login, password, repeatPassword))
		{
			registerMenu->reset();
			Menu::multiPopMenuStack(1);
		}
	});
	NME_FUNC_BUTTON("Назад", []() {
		registerMenu->reset();
		Menu::multiPopMenuStack(1);
	});

	registerMenu->initChosenElementIndex();
}

void initUserMenu()
{
	auto& menu = userMenu;
	if (menu) { delete menu; };
	menu = new Menu();

	NME_TITLE("Меню пользователя");
	NME_SUBTITLE("Работа");
	NME_FUNC_BUTTON("Действия с данными", []() { dataTypeMenu->addToStack(); });
	NME_FUNC_BUTTON("Выдать книгу", []() {});
	NME_SUBTITLE("Навигация");
	NME_FUNC_BUTTON("Назад", []() {
		userMenu->reset();
		User::getActiveUser() = nullptr;
		Menu::multiPopMenuStack(1);
	});

	userMenu->initChosenElementIndex();
}

void initAdminMenu()
{
	auto& menu = adminMenu;
	if (menu) { delete menu; };
	menu = new Menu();

	NME_TITLE("Меню администратора");
	NME_SUBTITLE("Управление");
	NME_FUNC_BUTTON("Действия с данными", []() { dataTypeMenu->addToStack(); });
	NME_FUNC_BUTTON("Манипуляции данными пользователей", []() {});
	NME_FUNC_BUTTON("Запросы на регистрацию", []() { initRegisterConfirmationMenu(); registerConfirmationMenu->addToStack(); });
	NME_FUNC_BUTTON("Блокировка пользователей", []() {});
	NME_FUNC_BUTTON("Логи", []() {});
	NME_SUBTITLE("Навигация");
	NME_FUNC_BUTTON("Назад", []() {
		adminMenu->reset();
		User::getActiveUser() = nullptr;
		Menu::multiPopMenuStack(1);
	});

	adminMenu->initChosenElementIndex();
}

void initStartMenu()
{
	auto& menu = startMenu;
	if (menu) { delete menu; };
	menu = new Menu();

	NME_TITLE("Информационная система национальной библиотеки");
	NME_SUBTITLE("Авторизация");
	NME_FUNC_BUTTON("Войти", []() {loginMenu->addToStack(); });
	NME_FUNC_BUTTON("Зарегистрироваться", []() {registerMenu->addToStack(); });
	NME_SUBTITLE("Навигация");
	NME_FUNC_BUTTON("Выйти из программы", []() {isLoopRunning = false; });

	startMenu->initChosenElementIndex();
}

void initDataTypeMenu()
{
	auto& menu = dataTypeMenu;
	if (menu) { delete menu; };
	menu = new Menu();

	NME_TITLE("Выбор типа данных");
	NME_SUBTITLE("Типы");
	NME_FUNC_BUTTON("Авторы", []() {});
	NME_FUNC_BUTTON("Читатели", []() {});
	NME_FUNC_BUTTON("Документы", []() {});
	NME_SUBTITLE("Навигация");
	NME_FUNC_BUTTON("Назад", []() { 
		dataTypeMenu->reset(); 
		Menu::multiPopMenuStack(1);
	});

	dataTypeMenu->initChosenElementIndex();
}

void initRegisterConfirmationMenu()
{
	auto& menu = registerConfirmationMenu;
	if (menu) { delete menu; };
	menu = new Menu();

	NME_TITLE("Запросы на регистрацию");
	NME_SUBTITLE("Неподтвержденные запросы");
	for (auto it : User::getBinderUnconfirmed().getRecords())
	{
		NME_CHOICE("ФИО: " + it->getFullName() + ", логин: " + it->getLogin(), {"Оставить неподтвержденным", "Подтвердить регистрацию", "Отклонить регистрацию"});
	}
	NME_SUBTITLE("Навигация");
	NME_FUNC_BUTTON("Сохранить", []() {
		// TODO: Тут считываем все данные и интерпретируем
		registerConfirmationMenu->reset();
		Menu::multiPopMenuStack(1);
	});
	NME_FUNC_BUTTON("Назад", []() {
		registerConfirmationMenu->reset();
		Menu::multiPopMenuStack(1);
	});

	registerConfirmationMenu->initChosenElementIndex();
}

void menuInitAll()
{
	initLoginMenu();
	initRegisterMenu();
	initAdminMenu();
	initUserMenu();
	initStartMenu();
	initDataTypeMenu();
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
			hasMenuChanged = true;
			g_lock.unlock();
		}
	}
}

void menuPrintLoop()
{
	while (isLoopRunning)
	{
		g_lock.lock();
		if (hasMenuChanged)
		{
			hasMenuChanged = false;
			system("cls");
			cout << Menu::getActive()->str();
		}
		g_lock.unlock();
		Sleep(100);
	}
}