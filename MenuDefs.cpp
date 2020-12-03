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
#include "ConstraintHelper.h"
#include "BindAwareDeleters.h"
#include <algorithm>
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

// FINISHED
void initLoginMenu()
{
	MI_START(loginMenu);
	NME_TITLE("Вход в систему");
	NME_SUBTITLE("Ввод данных");
	CH_NME_EDIT_FIELD("Логин", User, LOGIN);
	CH_NME_EDIT_FIELD_H("Пароль", User, PASSWORD);
	NME_SUBTITLE("Навигация");
	NME_FUNC_BUTTON("Войти", []() {
		CH_INIT;
		CH_MOVE(2);
		CH_GET_AS_EF_AND_CHECK(User, LOGIN, login);
		CH_MOVE(1);
		CH_GET_AS_EF_AND_CHECK(User, PASSWORD, password);
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

// FINISHED
void initRegisterMenu()
{
	MI_START(registerMenu);
	NME_TITLE("Регистрация");
	NME_SUBTITLE("Ввод данных");
	CH_NME_EDIT_FIELD("ФИО", Person, FULL_NAME);
	CH_NME_EDIT_FIELD("Логин", User, LOGIN);
	CH_NME_EDIT_FIELD_H("Пароль", User, PASSWORD);
	CH_NME_EDIT_FIELD_H("Повторите пароль", User, PASSWORD);
	NME_SUBTITLE("Навигация");
	NME_FUNC_BUTTON("Зарегистрироваться", []() {
		CH_INIT;
		CH_MOVE(2);
		CH_GET_AS_EF_AND_CHECK(Person, FULL_NAME, fullName);
		CH_MOVE(1);
		CH_GET_AS_EF_AND_CHECK(User, LOGIN, login);
		CH_MOVE(1);
		CH_GET_AS_EF_AND_CHECK(User, PASSWORD, password);
		CH_MOVE(1);
		CH_GET_AS_EF_AND_CHECK(User, PASSWORD, repeatPassword);
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

// FINISHED
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

// FINISHED
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

// FINISHED
void initStartMenu()
{
	MI_START(startMenu);
	NME_TITLE("Информационная система национальной библиотеки");
	NME_SUBTITLE("Авторизация");
	NME_FUNC_BUTTON("Войти", []() { loginMenu->addToStack(); });
	NME_FUNC_BUTTON("Зарегистрироваться", []() { registerMenu->addToStack(); });
	NME_SUBTITLE("Навигация");
	NME_FUNC_BUTTON("Выйти из программы", []() { Menu::finish(); });
	MI_END;
}

// FINISHED
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

// FINISHED
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

// FINISHED
void initAuthorListMenu()
{
	MI_START(authorListMenu);
	NME_TITLE("Список авторов");
	NME_SUBTITLE("Список");
	for (auto it : Author::getBinder().getRecords())
	{
		NME_FUNC_BUTTON(to_string(it->getId()) + ". " + it->getFullName(), []() { initAuthorEditMenu(); authorEditMenu->addToStack(); });
	}
	NME_SUBTITLE("Фильтрация и поиск");
	CH_NME_EDIT_FIELD("Содержит в ФИО", Person, FULL_NAME);
	NME_CHOICE("Сортировать по", {"ID", "ФИО"});
	NME_FUNC_BUTTON("Вывести результат", []() {
		vector<Author*>sorted(Author::getBinder().getRecords());
		CH_INIT;
		CH_MOVE(3 + Author::getBinder().getRecords().size());
		string t1 = CH_GET_AS(MenuElementEditField)->getInput();
		CH_MOVE(1);
		int t2 = CH_GET_AS(MenuElementChoice)->getActiveOption();
		if (t2 == 0)
		{
			sort(sorted.begin(), sorted.end(), [](Author *e1, Author* e2) {
				return e1->getId() < e2->getId();
			});
		}
		else if (t2 == 1)
		{
			sort(sorted.begin(), sorted.end(), [](Author *e1, Author* e2) {
				return e1->getFullName() < e2->getFullName();
			});
		}
		Menu::getMutex().lock();
		system("cls");
		for (auto it : sorted)
		{
			if (it->getFullName().find(t1) != string::npos)
			{
				cout << it->str() << endl;
			}
		}
		system("pause");
		Menu::getMutex().unlock();
	});
	NME_SUBTITLE("Навигация");
	NME_FUNC_BUTTON("Добавить автора", []() { authorAddMenu->addToStack(); });
	NME_FUNC_BUTTON("Назад", []() {
		authorListMenu->reset();
		Menu::multiPopMenuStack(1);
	});
	MI_END;
}

// TODO
void initDocumentListMenu()
{
	MI_START(documentListMenu);
	NME_TITLE("Список документов");
	NME_SUBTITLE("Список");
	for (auto it : Document::getBinder().getRecords())
	{
		NME_FUNC_BUTTON(it->str(), []() { initDocumentEditMenu(); documentEditMenu->addToStack(); });
	}
	NME_SUBTITLE("Параметры представления");
	CH_NME_EDIT_FIELD("Содержит в заголовке", Document, TITLE);
	CH_NME_EDIT_FIELD("Содержит в названии издателя", Publisher, NAME);
	CH_NME_EDIT_FIELD("Содержит в имени автора", Person, FULL_NAME);
	NME_CHOICE("Сортировать по", { "ID", "Заголовку", "ID издателя", "Издателю" });
	NME_FUNC_BUTTON("Вывести результат", []() {
		// TODO
	});
	NME_SUBTITLE("Навигация");
	NME_FUNC_BUTTON("Добавить документ", []() { initDocumentAddMenu(); documentAddMenu->addToStack(); });
	NME_FUNC_BUTTON("Назад", []() {
		documentListMenu->reset();
		Menu::multiPopMenuStack(1);
	});
	MI_END;
}

// TODO
void initReaderListMenu()
{
	MI_START(readerListMenu);
	NME_TITLE("Список читателей");
	NME_SUBTITLE("Список");
	for (auto it : Reader::getBinder().getRecords())
	{
		NME_FUNC_BUTTON(it->str(), []() { initReaderEditMenu(); readerEditMenu->addToStack(); });
	}
	NME_SUBTITLE("Параметры представления");
	CH_NME_EDIT_FIELD("Содержит в имени", Person, FULL_NAME);
	CH_NME_EDIT_FIELD("Содержит в ИН паспорта", Reader, PASSPORT_ID);
	NME_CHOICE("Сортировать по", { "ID", "Имени", "ИН паспорта" });
	NME_FUNC_BUTTON("Вывести результат", []() {
		// TODO
	});
	NME_SUBTITLE("Навигация");
	NME_FUNC_BUTTON("Добавить читателя", []() { readerAddMenu->addToStack(); });
	NME_FUNC_BUTTON("Назад", []() {
		readerListMenu->reset();
		Menu::multiPopMenuStack(1);
	});
	MI_END;
}

// TODO
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
	CH_NME_EDIT_FIELD("Содержит в названии", Publisher, NAME);
	NME_CHOICE("Сортировать по", { "ID", "Названию" });
	NME_FUNC_BUTTON("Вывести результат", []() {
		// TODO
	});
	NME_SUBTITLE("Навигация");
	NME_FUNC_BUTTON("Добавить издателя", []() { publisherAddMenu->addToStack(); });
	NME_FUNC_BUTTON("Назад", []() {
		publisherListMenu->reset();
		Menu::multiPopMenuStack(1);
	});
	MI_END;
}

// TODO
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
	CH_NME_EDIT_FIELD("Содержит в логине", User, LOGIN);
	CH_NME_EDIT_FIELD("Содержит в ФИО", Person, FULL_NAME);
	NME_CHOICE("Сортировать по", { "ID", "Логину", "ФИО" });
	NME_FUNC_BUTTON("Вывести результат", []() {
		// TODO
	});
	NME_SUBTITLE("Навигация");
	NME_FUNC_BUTTON("Добавить пользователя", []() { userAddMenu->addToStack(); });
	NME_FUNC_BUTTON("Назад", []() {
		userListMenu->reset();
		Menu::multiPopMenuStack(1);
	});
	MI_END;
}

// FINISHED
void initAuthorAddMenu()
{
	MI_START(authorAddMenu);
	NME_TITLE("Добавить автора");
	NME_SUBTITLE("Данные");
	CH_NME_EDIT_FIELD("ФИО", Person, FULL_NAME);
	NME_SUBTITLE("Навигация");
	NME_FUNC_BUTTON("Добавить", []() {
		CH_INIT;
		CH_MOVE(2);
		CH_GET_AS_EF_AND_CHECK(Person, FULL_NAME, fullName);
		Author::getBinder().getRecords().push_back(new Author(fullName));
		Author::getBinder().saveRecords();
		cout << "Добавление успешно." << endl;
		system("pause");
		authorAddMenu->reset();
		Menu::multiPopMenuStack(2);
		initAuthorListMenu();
		authorListMenu->addToStack();
	});
	NME_FUNC_BUTTON("Отмена", []() {
		authorAddMenu->reset();
		Menu::multiPopMenuStack(1);
	});
	MI_END;
}

// FINISHED
void initDocumentAddMenu()
{
	MI_START(documentAddMenu);
	NME_TITLE("Добавить документ");
	NME_SUBTITLE("Данные");
	CH_NME_EDIT_FIELD("Название", Document, TITLE);
	NME_CHOICE("Тип документа", Document::types);
	NME_CHOICE("Язык", Document::languages);
	vector<string> publishers;
	for (auto it : Publisher::getBinder().getRecords())
	{
		publishers.push_back(to_string(it->getId()));
	}
	NME_CHOICE("ID издателя", publishers);
	NME_CHOICE("Число страниц", 1, 2001);
	NME_SUBTITLE("Навигация");
	NME_FUNC_BUTTON("Добавить", []() {
		CH_INIT;
		CH_MOVE(2);
		CH_GET_AS_EF_AND_CHECK(Document, TITLE, title);
		CH_MOVE(1);
		int type = ((MenuElementChoice *)(*it))->getActiveOption();
		CH_MOVE(1);
		int language = ((MenuElementChoice *)(*it))->getActiveOption();
		CH_MOVE(1);
		string publisherId = ((MenuElementChoice *)(*it))->getChoice();
		CH_MOVE(1);
		int pageCount = stoi(((MenuElementChoice *)(*it))->getChoice());
		if (publisherId == MenuElementChoice::noChoicesFoundMessage)
		{
			cout << "Сохранение недопустимо -- список издателей пуст!" << endl;
			system("pause");
			return;
		}
		for (auto it : Publisher::getBinder().getRecords())
		{
			if (it->getId() == stoi(publisherId))
			{
				Document::getBinder().getRecords().push_back(new Document((Document::Type)type, (Document::Language)language, it, title, pageCount));
				break;
			}
		}
		Document::getBinder().saveRecords();
		cout << "Добавление успешно." << endl;
		system("pause");
		documentAddMenu->reset();
		Menu::multiPopMenuStack(2);
		initDocumentListMenu();
		documentListMenu->addToStack();
	});
	NME_FUNC_BUTTON("Отмена", []() {
		documentAddMenu->reset();
		Menu::multiPopMenuStack(1);
	});
	MI_END;
}

// FINISHED
void initReaderAddMenu()
{
	MI_START(readerAddMenu);
	NME_TITLE("Добавить читателя");
	NME_SUBTITLE("Данные");
	CH_NME_EDIT_FIELD("ФИО", Person, FULL_NAME);
	CH_NME_EDIT_FIELD("Номер телефона", Reader, PHONE_NUMBER);
	CH_NME_EDIT_FIELD("Адрес", Reader, ADDRESS);
	CH_NME_EDIT_FIELD("ИН паспорта", Reader, PASSPORT_ID);
	NME_SUBTITLE("Навигация");
	NME_FUNC_BUTTON("Добавить", []() {
		CH_INIT;
		CH_MOVE(2);
		CH_GET_AS_EF_AND_CHECK(Person, FULL_NAME, fullName);
		CH_MOVE(1);
		CH_GET_AS_EF_AND_CHECK(Reader, PHONE_NUMBER, phoneNumber);
		CH_MOVE(1);
		CH_GET_AS_EF_AND_CHECK(Reader, ADDRESS, address);
		CH_MOVE(1);
		CH_GET_AS_EF_AND_CHECK(Reader, PASSPORT_ID, passportId); 
		Reader::getBinder().getRecords().push_back(new Reader(fullName, phoneNumber, address, passportId));
		Reader::getBinder().saveRecords();
		readerAddMenu->reset();
		Menu::multiPopMenuStack(2);
		initReaderListMenu();
		readerListMenu->addToStack();
	});
	NME_FUNC_BUTTON("Отмена", []() {
		readerAddMenu->reset();
		Menu::multiPopMenuStack(1);
	});
	MI_END;
}

// FINISHED
void initPublisherAddMenu()
{
	MI_START(publisherAddMenu);
	NME_TITLE("Добавить издателя");
	NME_SUBTITLE("Данные");
	CH_NME_EDIT_FIELD("Название", Publisher, NAME);
	NME_SUBTITLE("Навигация");
	NME_FUNC_BUTTON("Добавить", []() {
		CH_INIT;
		CH_MOVE(2);
		CH_GET_AS_EF_AND_CHECK(Publisher, NAME, name);
		Publisher::getBinder().getRecords().push_back(new Publisher(name));
		Publisher::getBinder().saveRecords();
		publisherAddMenu->reset();
		Menu::multiPopMenuStack(2);
		initPublisherListMenu();
		publisherListMenu->addToStack();
	});
	NME_FUNC_BUTTON("Отмена", []() {
		publisherAddMenu->reset();
		Menu::multiPopMenuStack(1);
	});
	MI_END;
}

// FINISHED
void initUserAddMenu()
{
	MI_START(userAddMenu);
	NME_TITLE("Добавить пользователя");
	NME_SUBTITLE("Данные");
	CH_NME_EDIT_FIELD("ФИО", Person, FULL_NAME);
	CH_NME_EDIT_FIELD("Логин", User, LOGIN);
	CH_NME_EDIT_FIELD_H("Пароль", User, PASSWORD);
	CH_NME_EDIT_FIELD_H("Повторите пароль", User, PASSWORD);
	NME_SUBTITLE("Навигация");
	NME_FUNC_BUTTON("Зарегистрировать", []() {
		CH_INIT;
		CH_MOVE(2);
		CH_GET_AS_EF_AND_CHECK(Person, FULL_NAME, fullName);
		CH_MOVE(1);
		CH_GET_AS_EF_AND_CHECK(User, LOGIN, login);
		CH_MOVE(1);
		CH_GET_AS_EF_AND_CHECK(User, PASSWORD, password);
		CH_MOVE(1);
		CH_GET_AS_EF_AND_CHECK(User, PASSWORD, repeatPassword);
		if (User::registerUser(fullName, login, password, repeatPassword, true))
		{
			userAddMenu->reset();
			Menu::multiPopMenuStack(2);
			initUserListMenu();
			userListMenu->addToStack();
		}
	});
	NME_FUNC_BUTTON("Отмена", []() {
		userAddMenu->reset();
		Menu::multiPopMenuStack(1);
	});
	MI_END;
}

// FINISHED
void initAuthorEditMenu()
{
	MI_START(authorEditMenu);
	NME_TITLE("Редактировать автора");
	NME_SUBTITLE("Данные");
	CH_NME_EDIT_FIELD("ФИО", Person, FULL_NAME);
	GET_CTX(Author, author, 2);
	((MenuElementEditField *)ME_PREV)->getInput() = ctx->getFullName();
	NME_SUBTITLE("Навигация");
	NME_FUNC_BUTTON("Сохранить", []() {
		CH_INIT;
		CH_MOVE(2);
		CH_GET_AS_EF_AND_CHECK(Person, FULL_NAME, fullName);
		GET_CTX(Author, author, 2);
		ctx->getFullName() = CH_GET_AS(MenuElementEditField)->getInput();
		Author::getBinder().saveRecords();
		cout << "Изменение успешно." << endl;
		system("pause");
		Menu::multiPopMenuStack(2);
		initAuthorListMenu();
		authorListMenu->addToStack();
	});
	DOOM_BUTTON(Author, author);
	NME_FUNC_BUTTON("Отмена", []() {
		Menu::multiPopMenuStack(1);
	});
	MI_END;
}

vector<DocumentUseRecord *> results1;
vector<DocumentAuthorBind *> results2;

// TODO : Allow author add
void initDocumentEditMenu()
{
	GET_CTX(Document, document, 2);
	MI_START(documentEditMenu);
	NME_TITLE("Редактировать документ"); // 0
	DocumentUseRecord::searchByDocumentId(ctx->getId(), results1);
	if (results1.size())
	{
		NME_SUBTITLE("Последняя запись о выдаче: " + results1.back()->str(true)); // 1
	}
	else
	{
		NME_SUBTITLE("Нет записей о выдаче"); // 1
	}
	NME_SUBTITLE("Авторы"); // 2
	DocumentAuthorBind::searchByDocumentId(ctx->getId(), results2);
	for (auto it : results2)
	{
		NME_CHOICE(it->str(), {"Оставить", "Удалить"}); // 2 + [1..results2.size()]
	}
	NME_SUBTITLE("Данные"); // 3 + results2.size()
	CH_NME_EDIT_FIELD("Название", Document, TITLE); // 4 + results2.size()
	((MenuElementEditField *)ME_PREV)->getInput() = ctx->getTitle();
	NME_CHOICE("Тип документа", Document::types);	// 5 + results2.size()
	((MenuElementChoice *)ME_PREV)->getActiveOption() = (int)ctx->getType();
	NME_CHOICE("Язык", Document::languages); // 6 + results2.size()
	((MenuElementChoice *)ME_PREV)->getActiveOption() = (int)ctx->getLanguage();
	vector<string> publishers;
	for (auto it : Publisher::getBinder().getRecords())
	{
		publishers.push_back(to_string(it->getId()));
	}
	NME_CHOICE("ID издателя", publishers); // 7 + results2.size()
	{
		int localTmp = 0;
		int searchFor = ctx->getPublisher()->getId();
		for (auto it : Publisher::getBinder().getRecords())
		{
			if (it->getId() == searchFor)
			{
				((MenuElementChoice *)ME_PREV)->getActiveOption() = localTmp;
				break;
			}
			++localTmp;
		}
	}
	NME_CHOICE("Число страниц", 1, 2001); // 8 + results2.size()
	((MenuElementChoice *)ME_PREV)->getActiveOption() = ctx->getPageCount() - 1;
	NME_SUBTITLE("Опасная зона");
	DOOM_BUTTON(Document, document);
	NME_SUBTITLE("Навигация");
	NME_FUNC_BUTTON("Сохранить изменения", []() {
		GET_CTX(Document, document, 2);
		CH_INIT;
		CH_MOVE(results2.size() + 4);
		CH_GET_AS_EF_AND_CHECK(Document, TITLE, title);
		CH_MOVE(1);
		int type = ((MenuElementChoice *)(*it))->getActiveOption();
		CH_MOVE(1);
		int language = ((MenuElementChoice *)(*it))->getActiveOption();
		CH_MOVE(1);
		string publisherId = ((MenuElementChoice *)(*it))->getChoice();
		CH_MOVE(1);
		int pageCount = stoi(((MenuElementChoice *)(*it))->getChoice());
		if (publisherId == MenuElementChoice::noChoicesFoundMessage)
		{
			cout << "Сохранение недопустимо -- список издателей пуст!" << endl;
			system("pause");
			return;
		}
		for (auto it : Publisher::getBinder().getRecords())
		{
			if (it->getId() == stoi(publisherId))
			{
				GET_CTX(Document, document, 2);
				ctx->getType() = (Document::Type)type;
				ctx->getLanguage() = (Document::Language)language;
				ctx->getPublisher() = it;
				ctx->getTitle() = title;
				ctx->getPageCount() = pageCount;
				break;
			}
		}
		Document::getBinder().saveRecords();
		it = menuElements.begin();
		CH_MOVE(2 + results2.size());
		for (int i = results2.size() - 1; i >= 0; --i)
		{
			if (CH_GET_AS(MenuElementChoice)->getActiveOption() == 1)
			{
				DocumentAuthorBind::getBinder().getRecords().erase(DocumentAuthorBind::getBinder().getRecords().begin() + i);
			}
			CH_MOVE(-1);
		}
		DocumentAuthorBind::getBinder().saveRecords();
		Menu::multiPopMenuStack(2);
		initDocumentListMenu();
		documentListMenu->addToStack();
	});	
	NME_FUNC_BUTTON("Отмена", []() {
		documentEditMenu->reset();
		Menu::multiPopMenuStack(1);
	});
	MI_END;
}

// TODO
void initReaderEditMenu()
{
	MI_START(readerEditMenu);
	NME_TITLE("Редактировать читателя");
	NME_SUBTITLE("Данные");
	NME_SUBTITLE("Навигация");
	NME_FUNC_BUTTON("Отмена", []() {
		Menu::multiPopMenuStack(1);
	});
	MI_END;
}

// TODO
void initPublisherEditMenu()
{
	MI_START(publisherEditMenu);
	NME_TITLE("Редактировать издателя");
	NME_SUBTITLE("Данные");
	NME_SUBTITLE("Навигация");
	NME_FUNC_BUTTON("Отмена", []() {
		Menu::multiPopMenuStack(1);
	});
	MI_END;
}

// TODO
void initUserEditMenu()
{
	MI_START(userEditMenu);
	NME_TITLE("Редактировать пользователя");
	NME_SUBTITLE("Данные");
	NME_SUBTITLE("Навигация");
	NME_FUNC_BUTTON("Отмена", []() {
		Menu::multiPopMenuStack(1);
	});
	MI_END;
}

// TODO
void initLogMenu()
{
	MI_START(logMenu);
	NME_TITLE("Просмотр логов");
	NME_SUBTITLE("Список");
	//TODO Здесь будет выводиться список сохраненных ротаций логов
	NME_SUBTITLE("Навигация");
	NME_FUNC_BUTTON("Назад", []() {
		Menu::multiPopMenuStack(1);
	});
	MI_END;
}

// FINISHED
void initDocumentGivingMenu()
{
	MI_START(documentGivingMenu);
	NME_TITLE("Выдача документов");
	NME_SUBTITLE("Выбор");
	vector<string> readers;
	for (auto it : Reader::getBinder().getRecords())
	{
		readers.push_back(to_string(it->getId()));
	}
	NME_CHOICE("ID читателя", readers);
	vector<string> documents;
	for (auto it : Document::getBinder().getRecords())
	{
		documents.push_back(to_string(it->getId()));
	}
	NME_CHOICE("ID документа", documents);
	NME_CHOICE("Выдать на какое время (в часах)", 1, 721);
	NME_SUBTITLE("Навигация");
	NME_FUNC_BUTTON("Подтвердить выдачу", [](){
		string choiceReader = ((MenuElementChoice *)(documentGivingMenu->getElements()[2]))->getChoice();
		if (choiceReader == MenuElementChoice::noChoicesFoundMessage)
		{
			documentGivingMenu->reset();
			Menu::multiPopMenuStack(1);
			return;
		}
		string choiceDocument = ((MenuElementChoice *)(documentGivingMenu->getElements()[3]))->getChoice();
		if (choiceDocument == MenuElementChoice::noChoicesFoundMessage)
		{
			documentGivingMenu->reset();
			Menu::multiPopMenuStack(1);
			return;
		}
		for (auto reader_it : Reader::getBinder().getRecords())
		{
			if (reader_it->getId() == stoi(choiceReader))
			{
				for (auto document_it : Document::getBinder().getRecords())
				{
					if (document_it->getId() == stoi(choiceDocument))
					{
						DocumentUseRecord::getBinder().getRecords().push_back(new DocumentUseRecord(
							document_it,
							reader_it,
							time(0),
							stoi(((MenuElementChoice *)(documentGivingMenu->getElements()[4]))->getChoice())
						));
						break;
					}
				}
				break;
			}
		}
		DocumentUseRecord::getBinder().saveRecords();
		documentGivingMenu->reset();
		Menu::multiPopMenuStack(1);
	});
	NME_FUNC_BUTTON("Отмена", []() {
		documentGivingMenu->reset();
		Menu::multiPopMenuStack(1);
	});
	MI_END;
}

int _readerDebtListMenu_chosenReaderId = -1;
int _readerDebtListMenu_chosenReaderVectorIndex = -1;

// FINISHED
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
	if (_readerDebtListMenu_chosenReaderVectorIndex != -1)
	{
		((MenuElementChoice *)(ME_PREV))->getActiveOption() = _readerDebtListMenu_chosenReaderVectorIndex;
	}
	NME_FUNC_BUTTON("Выбрать читателя без сохранения данных", []() {
		if (((MenuElementChoice *)(readerDebtListMenu->getElements()[2]))->getOptions().size())
		{
			_readerDebtListMenu_chosenReaderId = stoi(((MenuElementChoice *)(readerDebtListMenu->getElements()[2]))->getChoice());
			_readerDebtListMenu_chosenReaderVectorIndex = ((MenuElementChoice *)(readerDebtListMenu->getElements()[2]))->getActiveOption();
		}
		else
		{
			_readerDebtListMenu_chosenReaderId = -1;
			_readerDebtListMenu_chosenReaderVectorIndex = -1;
		}
		readerDebtListMenu->reset();
		Menu::multiPopMenuStack(1);
		initReaderDebtListMenu();
		readerDebtListMenu->addToStack();
	});
	NME_FUNC_BUTTON("Сохранить данные и выбрать читателя", []() {
		if (_readerDebtListMenu_chosenReaderVectorIndex != 1)
		{
			CH_INIT;
			CH_MOVE(5 + DocumentUseRecord::getBinder().getRecords().size());
			for (int i = DocumentUseRecord::getBinder().getRecords().size() - 1; i >= 0; --i)
			{
				if(CH_GET_AS(MenuElementChoice)->getActiveOption() == 1)
				{
					delete DocumentUseRecord::getBinder().getRecords()[i];
					DocumentUseRecord::getBinder().getRecords().erase(DocumentUseRecord::getBinder().getRecords().begin() + i);
				}
				CH_MOVE(-1);
			}
		}
		DocumentUseRecord::getBinder().saveRecords();
		if (((MenuElementChoice *)(readerDebtListMenu->getElements()[2]))->getOptions().size())
		{
			_readerDebtListMenu_chosenReaderId = stoi(((MenuElementChoice *)(readerDebtListMenu->getElements()[2]))->getChoice());
			_readerDebtListMenu_chosenReaderVectorIndex = ((MenuElementChoice *)(readerDebtListMenu->getElements()[2]))->getActiveOption();
		}
		else
		{
			_readerDebtListMenu_chosenReaderId = -1;
			_readerDebtListMenu_chosenReaderVectorIndex = -1;
		}
		readerDebtListMenu->reset();
		Menu::multiPopMenuStack(1);
		initReaderDebtListMenu();
		readerDebtListMenu->addToStack();
	});
	if (_readerDebtListMenu_chosenReaderId == -1)
	{
		NME_SUBTITLE("Читатель не выбран. Выберите читателя и подтвердите выбор.");
	}
	else
	{
		NME_SUBTITLE("Задолженности читателя");
		for (auto it : DocumentUseRecord::getBinder().getRecords())
		{
			if (_readerDebtListMenu_chosenReaderId == it->getReader()->getId())
			{
				NME_CHOICE(it->getDocument()->getTitle() + " [" + it->getDocument()->getPublisher()->getName() + "]", { "Без изменений", "Закрыть задолженность" });
			}
		}
	}
	NME_SUBTITLE("Навигация");
	NME_FUNC_BUTTON("Сохранить и выйти", []() {
		if (_readerDebtListMenu_chosenReaderVectorIndex != 1)
		{
			CH_INIT;
			CH_MOVE(5 + DocumentUseRecord::getBinder().getRecords().size());
			for (int i = DocumentUseRecord::getBinder().getRecords().size() - 1; i >= 0; --i)
			{
				if (CH_GET_AS(MenuElementChoice)->getActiveOption() == 1)
				{
					delete DocumentUseRecord::getBinder().getRecords()[i];
					DocumentUseRecord::getBinder().getRecords().erase(DocumentUseRecord::getBinder().getRecords().begin() + i);
				}
				CH_MOVE(-1);
			}
		}
		DocumentUseRecord::getBinder().saveRecords();
		readerDebtListMenu->reset();
		Menu::multiPopMenuStack(1);
		_readerDebtListMenu_chosenReaderId = -1;
		_readerDebtListMenu_chosenReaderVectorIndex = -1;
	});
	NME_FUNC_BUTTON("Отмена", []() {
		readerDebtListMenu->reset();
		Menu::multiPopMenuStack(1);
		_readerDebtListMenu_chosenReaderId = -1;
		_readerDebtListMenu_chosenReaderVectorIndex = -1;
	});
	MI_END;
}

// FINISHED
void menuInitAll()
{
	initLoginMenu();
	initRegisterMenu();
	initAdminMenu();
	initUserMenu();
	initStartMenu();
	initDataTypeMenu();
	initAuthorAddMenu();
	initReaderAddMenu();
	initPublisherAddMenu();
	initUserAddMenu();
	startMenu->addToStack();
}
