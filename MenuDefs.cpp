#include "pch.h"
#include "MenuDefs.h"
#include "Menu.h"
#include "MenuElements.h"
#include "User.h"
#include "Publisher.h"
#include "Document.h"
#include "Author.h"
#include "Reader.h"
#include "DocumentAuthorBind.h"
#include "DocumentUseRecord.h"
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
Menu* authorListMenu = nullptr;
Menu* readerListMenu = nullptr;
Menu* documentListMenu = nullptr;
Menu* publisherListMenu = nullptr;
Menu* userListMenu = nullptr;
Menu* authorAddMenu = nullptr;
Menu* readerAddMenu = nullptr;
Menu* documentAddMenu = nullptr;
Menu* publisherAddMenu = nullptr;
Menu* userAddMenu = nullptr;
Menu* authorEditMenu = nullptr;
Menu* readerEditMenu = nullptr;
Menu* documentEditMenu = nullptr;
Menu* publisherEditMenu = nullptr;
Menu* userEditMenu = nullptr;
Menu* logMenu = nullptr;
Menu* documentGivingMenu = nullptr;
Menu* readerDebtListMenu = nullptr;

bool isLoopRunning = true;
bool hasMenuChanged = true;
mutex g_lock;
long elapsed;

void initLoginMenu()
{
	MI_START(loginMenu);
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
	NME_FUNC_BUTTON("Отмена", []() {
		loginMenu->reset();
		Menu::multiPopMenuStack(1);
	});
	MI_END;
}

void initRegisterMenu()
{
	MI_START(registerMenu);
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
	NME_FUNC_BUTTON("Отмена", []() {
		registerMenu->reset();
		Menu::multiPopMenuStack(1);
	});
	MI_END;
}

void initUserMenu()
{
	MI_START(userMenu);
	NME_TITLE("Меню пользователя");
	NME_SUBTITLE("Работа");
	NME_FUNC_BUTTON("Действия с данными", []() { dataTypeMenu->addToStack(); });
	NME_FUNC_BUTTON("Выдать документ", []() { initDocumentGivingMenu(); documentGivingMenu->addToStack(); });
	NME_FUNC_BUTTON("Просмотреть задолженности читателя", []() { initReaderDebtListMenu(); readerDebtListMenu->addToStack(); });
	NME_SUBTITLE("Навигация");
	NME_FUNC_BUTTON("Назад", []() {
		userMenu->reset();
		User::getActiveUser() = nullptr;
		Menu::multiPopMenuStack(1);
	});
	MI_END;
}

void initAdminMenu()
{
	MI_START(adminMenu);
	NME_TITLE("Меню администратора");
	NME_SUBTITLE("Управление");
	NME_FUNC_BUTTON("Действия с данными", []() { dataTypeMenu->addToStack(); });
	NME_FUNC_BUTTON("Действия с пользователями", []() { initUserListMenu(); userListMenu->addToStack(); });
	NME_FUNC_BUTTON("Запросы на регистрацию", []() { initRegisterConfirmationMenu(); registerConfirmationMenu->addToStack(); });
	NME_FUNC_BUTTON("Просмотр логов", []() { initLogMenu(); logMenu->addToStack(); });
	NME_SUBTITLE("Навигация");
	NME_FUNC_BUTTON("Назад", []() {
		adminMenu->reset();
		User::getActiveUser() = nullptr;
		Menu::multiPopMenuStack(1);
	});
	MI_END;
}

void initStartMenu()
{
	MI_START(startMenu);
	NME_TITLE("Информационная система национальной библиотеки");
	NME_SUBTITLE("Авторизация");
	NME_FUNC_BUTTON("Войти", []() {loginMenu->addToStack(); });
	NME_FUNC_BUTTON("Зарегистрироваться", []() {registerMenu->addToStack(); });
	NME_SUBTITLE("Навигация");
	NME_FUNC_BUTTON("Выйти из программы", []() {isLoopRunning = false; });
	MI_END;
}

void initDataTypeMenu()
{
	MI_START(dataTypeMenu);
	NME_TITLE("Выбор типа данных");
	NME_SUBTITLE("Типы");
	NME_FUNC_BUTTON("Авторы", []() { initAuthorListMenu(); authorListMenu->addToStack(); });
	NME_FUNC_BUTTON("Читатели", []() { initReaderListMenu(); readerListMenu->addToStack(); });
	NME_FUNC_BUTTON("Документы", []() { initDocumentListMenu(); documentListMenu->addToStack(); });
	NME_FUNC_BUTTON("Издатели", []() { initPublisherListMenu(); publisherListMenu->addToStack(); });
	NME_SUBTITLE("Навигация");
	NME_FUNC_BUTTON("Назад", []() { 
		dataTypeMenu->reset(); 
		Menu::multiPopMenuStack(1);
	});
	MI_END;
}

void initRegisterConfirmationMenu()
{
	MI_START(registerConfirmationMenu);
	NME_TITLE("Запросы на регистрацию");
	NME_SUBTITLE("Неподтвержденные запросы");
	for (auto it : User::getBinderUnconfirmed().getRecords())
	{
		NME_CHOICE("ФИО: " + it->getFullName() + ", логин: " + it->getLogin(), {"Оставить неподтвержденным", "Подтвердить регистрацию", "Отклонить регистрацию"});
	}
	NME_SUBTITLE("Навигация");
	NME_FUNC_BUTTON("Сохранить", []() {
		auto elemIt = registerConfirmationMenu->getElements().begin();
		elemIt += 2;
		int offset = 0;
		int size = User::getBinderUnconfirmed().getRecords().size();
		for (int i = 0; i < size; ++i)
		{
			if (((MenuElementChoice*)(*elemIt))->getChoice() == "Подтвердить регистрацию")
			{
				User::getBinder().getRecords().push_back(User::getBinderUnconfirmed().getRecords()[i-offset]);
				User::getBinderUnconfirmed().getRecords().erase(User::getBinderUnconfirmed().getRecords().begin()+i-offset);
				++offset;
			}
			else if (((MenuElementChoice*)(*elemIt))->getChoice() == "Отклонить регистрацию")
			{
				User::getBinderUnconfirmed().getRecords().erase(User::getBinderUnconfirmed().getRecords().begin() + i - offset);
				++offset;
			}
			++elemIt;
		}
		User::getBinder().saveRecords();
		User::getBinderUnconfirmed().saveRecords();
		registerConfirmationMenu->reset();
		Menu::multiPopMenuStack(1);
	});
	NME_FUNC_BUTTON("Назад", []() {
		registerConfirmationMenu->reset();
		Menu::multiPopMenuStack(1);
	});
	MI_END;
}

void initAuthorListMenu()
{
	MI_START(authorListMenu);
	NME_TITLE("Список авторов");
	NME_SUBTITLE("Список");
	for (auto it : Author::getBinder().getRecords())
	{
		NME_FUNC_BUTTON(to_string(it->getId()) + ". " + it->getFullName(), []() { initAuthorEditMenu(); authorEditMenu->addToStack(); });
	}
	NME_SUBTITLE("Параметры представления");
	// TODO
	NME_SUBTITLE("Навигация");
	NME_FUNC_BUTTON("Назад", []() {
		authorListMenu->reset();
		Menu::multiPopMenuStack(1);
	});
	MI_END;
}

void initDocumentListMenu()
{
	MI_START(documentListMenu);
	NME_TITLE("Список документов");
	NME_SUBTITLE("Список");
	for (auto it : Document::getBinder().getRecords())
	{
		NME_FUNC_BUTTON(to_string(it->getId()) + ". " + it->getTitle() + " [" + it->getPublisher()->getName() + "]", []() { initDocumentEditMenu(); documentEditMenu->addToStack(); });
	}
	NME_SUBTITLE("Параметры представления");
	// TODO
	NME_SUBTITLE("Навигация");
	NME_FUNC_BUTTON("Назад", []() {
		documentListMenu->reset();
		Menu::multiPopMenuStack(1);
	});
	MI_END;
}

void initReaderListMenu()
{
	MI_START(readerListMenu);
	NME_TITLE("Список читателей");
	NME_SUBTITLE("Список");
	for (auto it : Reader::getBinder().getRecords())
	{
		NME_FUNC_BUTTON(it->getId() + ". " + it->getFullName() + " ["+ it->getPassportId() +"]", []() { initReaderEditMenu(); readerEditMenu->addToStack(); });
	}
	NME_SUBTITLE("Параметры представления");
	// TODO
	NME_SUBTITLE("Навигация");
	NME_FUNC_BUTTON("Назад", []() {
		readerListMenu->reset();
		Menu::multiPopMenuStack(1);
	});
	MI_END;
}

void initPublisherListMenu()
{
	MI_START(publisherListMenu);
	NME_TITLE("Список издателей");
	NME_SUBTITLE("Список");
	for (auto it : Publisher::getBinder().getRecords())
	{
		NME_FUNC_BUTTON(to_string(it->getId()) + ". " + it->getName(), []() { initPublisherEditMenu(); publisherEditMenu->addToStack(); });
	}
	NME_SUBTITLE("Параметры представления");
	// TODO
	NME_SUBTITLE("Навигация");
	NME_FUNC_BUTTON("Назад", []() {
		publisherListMenu->reset();
		Menu::multiPopMenuStack(1);
	});
	MI_END;
}

void initUserListMenu()
{
	MI_START(userListMenu);
	NME_TITLE("Список пользователей");
	NME_SUBTITLE("Список");
	for (auto it : User::getBinder().getRecords())
	{
		NME_FUNC_BUTTON(it->getLogin() + ". " + it->getFullName(), []() { initUserEditMenu(); userEditMenu->addToStack(); });
	}
	NME_SUBTITLE("Параметры представления");
	// TODO
	NME_SUBTITLE("Навигация");
	NME_FUNC_BUTTON("Назад", []() {
		userListMenu->reset();
		Menu::multiPopMenuStack(1);
	});
	MI_END;
}

void initAuthorAddMenu()
{
}

void initDocumentAddMenu()
{
}

void initReaderAddMenu()
{
}

void initPublisherAddMenu()
{
}

void initUserAddMenu()
{
}

void initAuthorEditMenu()
{
}

void initDocumentEditMenu()
{
}

void initReaderEditMenu()
{
}

void initPublisherEditMenu()
{
}

void initUserEditMenu()
{
}

void initLogMenu()
{
	MI_START(logMenu);
	NME_TITLE("Просмотр логов");
	NME_SUBTITLE("Список");
	//TODO Здесь будет выводиться список сохраненных ротаций логов
	NME_SUBTITLE("Навигация");
	NME_FUNC_BUTTON("Назад", []() {
		logMenu->reset();
		Menu::multiPopMenuStack(1);
	});
	MI_END;
}

void initDocumentGivingMenu()
{
	MI_START(documentGivingMenu);
	NME_TITLE("Выдача документов");
	NME_SUBTITLE("Выбор");
	//TODO
	// Здесь будет choice из возможных айди читателей. По легенде библиотекарь знает айди читателя из его читательского билета.
	NME_CHOICE("ID читателя", {});
	// Здесь будет choice из возможных айди документов, ибо другие реализации слишком сложны. Библиотекарь предварительно ищет документы для читателя через другое меню.
	NME_CHOICE("ID документа", {});
	NME_SUBTITLE("Навигация");
	NME_FUNC_BUTTON("Подтвердить выдачу", [](){});
	NME_FUNC_BUTTON("Отмена", []() {
		documentGivingMenu->reset();
		Menu::multiPopMenuStack(1);
	});
	MI_END;
}

int _chosenReaderIdForDebtListing = -1;

void initReaderDebtListMenu()
{
	MI_START(readerDebtListMenu);
	NME_TITLE("Список задолженностей");
	NME_SUBTITLE("Выбор читателя");
	vector<string> readers;
	for (auto it : Reader::getBinder().getRecords())
	{
		readers.push_back(to_string(it->getId()));
	}
	NME_CHOICE("ID читателя", readers);
	NME_FUNC_BUTTON("Выбрать читателя без сохранения данных", []() {
		if (((MenuElementChoice *)(readerDebtListMenu->getElements()[2]))->getOptions().size())
		{
			_chosenReaderIdForDebtListing = stoi(((MenuElementChoice *)(readerDebtListMenu->getElements()[2]))->getChoice());
		}
		else
		{
			_chosenReaderIdForDebtListing = -1;
		}
		readerDebtListMenu->reset();
		Menu::multiPopMenuStack(1);
		initReaderDebtListMenu();
		readerDebtListMenu->addToStack();
	});
	NME_FUNC_BUTTON("Сохранить данные и выбрать читателя", []() {
		// TODO data save
		DocumentUseRecord::getBinder().saveRecords();
		if (((MenuElementChoice *)(readerDebtListMenu->getElements()[2]))->getOptions().size())
		{
			_chosenReaderIdForDebtListing = stoi(((MenuElementChoice *)(readerDebtListMenu->getElements()[2]))->getChoice());
		}
		else
		{
			_chosenReaderIdForDebtListing = -1;
		}
		readerDebtListMenu->reset();
		Menu::multiPopMenuStack(1);
		initReaderDebtListMenu();
		readerDebtListMenu->addToStack();
	});
	NME_SUBTITLE("Задолженности читателя");
	for (auto it : DocumentUseRecord::getBinder().getRecords())
	{
		if (_chosenReaderIdForDebtListing == it->getReader()->getId())
		{
			NME_CHOICE(it->getDocument()->getTitle() + " [" + it->getDocument()->getPublisher()->getName() + "]", { "Без изменений", "Закрыть задолженность" });
		}
	}
	NME_SUBTITLE("Навигация");
	NME_FUNC_BUTTON("Сохранить и выйти", []() {
		// TODO data save
		DocumentUseRecord::getBinder().saveRecords();
		readerDebtListMenu->reset();
		Menu::multiPopMenuStack(1);
		_chosenReaderIdForDebtListing = -1;
	});
	NME_FUNC_BUTTON("Отмена", []() {
		readerDebtListMenu->reset();
		Menu::multiPopMenuStack(1);
		_chosenReaderIdForDebtListing = -1;
	});
	MI_END;
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