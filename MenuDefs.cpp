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

string _authorListFilterFullName = "";
string _authorListSortBy = "ID";

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
	NME_EDIT_FIELD("Содержит в ФИО");
	NME_CHOICE("Сортировать по", {"ID", "ФИО"});
	NME_FUNC_BUTTON("Применить параметры", []() {
		// TODO
	});
	NME_SUBTITLE("Навигация");
	NME_FUNC_BUTTON("Добавить автора", []() { authorAddMenu->addToStack(); });
	NME_FUNC_BUTTON("Назад", []() {
		authorListMenu->reset();
		Menu::multiPopMenuStack(1);
	});
	MI_END;
}

string _documentListFilterTitle = "";
string _documentListFilterPublisherName = "";
string _documentListSortBy = "ID";

void initDocumentListMenu()
{
	MI_START(documentListMenu);
	NME_TITLE("Список документов");
	NME_SUBTITLE("Список");
	for (auto it : Document::getBinder().getRecords())
	{
		NME_FUNC_BUTTON(to_string(it->getId()) + ". " + it->getTitle() + " [" + to_string(it->getPublisher()->getId()) + ". " + it->getPublisher()->getName() + "]", []() { initDocumentEditMenu(); documentEditMenu->addToStack(); });
	}
	NME_SUBTITLE("Параметры представления");
	NME_EDIT_FIELD("Содержит в заголовке");
	NME_EDIT_FIELD("Содержит в названии издателя");
	NME_CHOICE("Сортировать по", { "ID", "Заголовку", "ID издателя", "Издателю" });
	NME_FUNC_BUTTON("Применить параметры", []() {
		// TODO
	});
	NME_SUBTITLE("Навигация");
	NME_FUNC_BUTTON("Добавить документ", []() { documentAddMenu->addToStack(); });
	NME_FUNC_BUTTON("Назад", []() {
		documentListMenu->reset();
		Menu::multiPopMenuStack(1);
	});
	MI_END;
}

string _readerListFilterName = "";
string _readerListFilterPassportId = "";
string _readerListSortBy = "ID";

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
	NME_EDIT_FIELD("Содержит в имени");
	NME_EDIT_FIELD("Содержит в ИН паспорта");
	NME_CHOICE("Сортировать по", { "ID", "Имени", "ИН паспорта" });
	NME_FUNC_BUTTON("Применить параметры", []() {
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

string _publisherListFilterName = "";
string _publisherListSortBy = "ID";

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
	NME_EDIT_FIELD("Содержит в названии");
	NME_CHOICE("Сортировать по", { "ID", "Названию" });
	NME_FUNC_BUTTON("Применить параметры", []() {
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

string _userListFilterLogin = "";
string _userListFilterFullName = "";
string _userListSortBy = "ID";

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
	NME_EDIT_FIELD("Содержит в логине");
	NME_EDIT_FIELD("Содержит в ФИО");
	NME_CHOICE("Сортировать по", { "ID", "Логину", "ФИО" });
	NME_FUNC_BUTTON("Применить параметры", []() {
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

void initAuthorAddMenu()
{
	MI_START(authorAddMenu);
	NME_TITLE("Добавить автора");
	NME_SUBTITLE("Данные");
	NME_EDIT_FIELD("ФИО", false, Constraints::Person::FULL_NAME_ALLOWED_CHARS, Constraints::Person::FULL_NAME_MAX_LENGTH);
	NME_SUBTITLE("Навигация");
	NME_FUNC_BUTTON("Добавить", []() {
		auto menuElements = Menu::getActive()->getElements();
		string fullName;
		auto it = menuElements.begin();
		it += 2;
		fullName = ((MenuElementEditField *)(*it))->getInput();
		if (fullName.length() < Constraints::Person::FULL_NAME_MIN_LENGTH)
		{
			cout << "Длина имени не может быть меньше " << Constraints::Person::FULL_NAME_MIN_LENGTH << " символов." << endl;
			system("pause");
		}
		else
		{
			Author::getBinder().getRecords().push_back(new Author(fullName));
			Author::getBinder().saveRecords();
			cout << "Добавление успешно." << endl;
			system("pause");
			authorAddMenu->reset();
			Menu::multiPopMenuStack(2);
			initAuthorListMenu();
			authorListMenu->addToStack();
		}
	});
	NME_FUNC_BUTTON("Отмена", []() {
		authorAddMenu->reset();
		Menu::multiPopMenuStack(1);
	});
	MI_END;
}

void initDocumentAddMenu()
{
	MI_START(documentAddMenu);
	NME_TITLE("Добавить документ");
	NME_SUBTITLE("Данные");
	NME_SUBTITLE("Навигация");
	NME_FUNC_BUTTON("Отмена", []() {
		documentAddMenu->reset();
		Menu::multiPopMenuStack(1);
	});
	MI_END;
}

void initReaderAddMenu()
{
	MI_START(readerAddMenu);
	NME_TITLE("Добавить читателя");
	NME_SUBTITLE("Данные");
	NME_SUBTITLE("Навигация");
	NME_FUNC_BUTTON("Отмена", []() {
		readerAddMenu->reset();
		Menu::multiPopMenuStack(1);
	});
	MI_END;
}

void initPublisherAddMenu()
{
	MI_START(publisherAddMenu);
	NME_TITLE("Добавить издателя");
	NME_SUBTITLE("Данные");
	NME_SUBTITLE("Навигация");
	NME_FUNC_BUTTON("Отмена", []() {
		publisherAddMenu->reset();
		Menu::multiPopMenuStack(1);
	});
	MI_END;
}

void initUserAddMenu()
{
	MI_START(userAddMenu);
	NME_TITLE("Добавить пользователя");
	NME_SUBTITLE("Данные");
	NME_EDIT_FIELD("ФИО", false, Constraints::Person::FULL_NAME_ALLOWED_CHARS, Constraints::Person::FULL_NAME_MAX_LENGTH);
	NME_EDIT_FIELD("Логин", false, Constraints::User::LOGIN_ALLOWED_CHARS, Constraints::User::LOGIN_MAX_LENGTH);
	NME_EDIT_FIELD("Пароль", true, Constraints::User::PASSWORD_ALLOWED_CHARS, Constraints::User::PASSWORD_MAX_LENGTH);
	NME_EDIT_FIELD("Повторите пароль", true, Constraints::User::PASSWORD_ALLOWED_CHARS, Constraints::User::PASSWORD_MAX_LENGTH);
	NME_SUBTITLE("Навигация");
	NME_FUNC_BUTTON("Зарегистрировать", []() {
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

void initAuthorEditMenu()
{
	MI_START(authorEditMenu);
	NME_TITLE("Редактировать автора");
	NME_SUBTITLE("Данные");
	NME_SUBTITLE("Навигация");
	NME_FUNC_BUTTON("Отмена", []() {
		Menu::multiPopMenuStack(1);
	});
	MI_END;
}

void initDocumentEditMenu()
{
	MI_START(documentEditMenu);
	NME_TITLE("Редактировать документ");
	NME_SUBTITLE("Данные");
	NME_SUBTITLE("Навигация");
	NME_FUNC_BUTTON("Отмена", []() {
		Menu::multiPopMenuStack(1);
	});
	MI_END;
}

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
	NME_CHOICE("Выдать на какое время (в часах)", { 
		"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20",
		"21", "22", "23", "24", "25", "26", "27", "28", "29", "30", "31", "32", "33", "34", "35", "36", "37", "38", "39", "40",
		"41", "42", "43", "44", "45", "46", "47", "48", "49", "50", "51", "52", "53", "54", "55", "56", "57", "58", "59", "60",
		"61", "62", "63", "64", "65", "66", "67", "68", "69", "70", "71", "72", "73", "74", "75", "76", "77", "78", "79", "80",
		"81", "82", "83", "84", "85", "86", "87", "88", "89", "90", "91", "92", "93", "94", "95", "96", "97", "98", "99", "100",
		"101", "102", "103", "104", "105", "106", "107", "108", "109", "110", "111", "112", "113", "114", "115", "116", "117", "118", "119", "120",
		"121", "122", "123", "124", "125", "126", "127", "128", "129", "130", "131", "132", "133", "134", "135", "136", "137", "138", "139", "140",
		"141", "142", "143", "144", "145", "146", "147", "148", "149", "150", "151", "152", "153", "154", "155", "156", "157", "158", "159", "160",
		"161", "162", "163", "164", "165", "166", "167", "168", "169", "170", "171", "172", "173", "174", "175", "176", "177", "178", "179", "180",
		"181", "182", "183", "184", "185", "186", "187", "188", "189", "190", "191", "192", "193", "194", "195", "196", "197", "198", "199", "200",
		"201", "202", "203", "204", "205", "206", "207", "208", "209", "210", "211", "212", "213", "214", "215", "216", "217", "218", "219", "220",
		"221", "222", "223", "224", "225", "226", "227", "228", "229", "230", "231", "232", "233", "234", "235", "236", "237", "238", "239", "240",
		"241", "242", "243", "244", "245", "246", "247", "248", "249", "250", "251", "252", "253", "254", "255", "256", "257", "258", "259", "260",
		"261", "262", "263", "264", "265", "266", "267", "268", "269", "270", "271", "272", "273", "274", "275", "276", "277", "278", "279", "280",
		"281", "282", "283", "284", "285", "286", "287", "288", "289", "290", "291", "292", "293", "294", "295", "296", "297", "298", "299", "300",
		"301", "302", "303", "304", "305", "306", "307", "308", "309", "310", "311", "312", "313", "314", "315", "316", "317", "318", "319", "320",
		"321", "322", "323", "324", "325", "326", "327", "328", "329", "330", "331", "332", "333", "334", "335", "336", "337", "338", "339", "340",
		"341", "342", "343", "344", "345", "346", "347", "348", "349", "350", "351", "352", "353", "354", "355", "356", "357", "358", "359", "360",
		"361", "362", "363", "364", "365", "366", "367", "368", "369", "370", "371", "372", "373", "374", "375", "376", "377", "378", "379", "380",
		"381", "382", "383", "384", "385", "386", "387", "388", "389", "390", "391", "392", "393", "394", "395", "396", "397", "398", "399", "400",
		"401", "402", "403", "404", "405", "406", "407", "408", "409", "410", "411", "412", "413", "414", "415", "416", "417", "418", "419", "420",
		"421", "422", "423", "424", "425", "426", "427", "428", "429", "430", "431", "432", "433", "434", "435", "436", "437", "438", "439", "440",
		"441", "442", "443", "444", "445", "446", "447", "448", "449", "450", "451", "452", "453", "454", "455", "456", "457", "458", "459", "460", 
		"461", "462", "463", "464", "465", "466", "467", "468", "469", "470", "471", "472", "473", "474", "475", "476", "477", "478", "479", "480", 
		"481", "482", "483", "484", "485", "486", "487", "488", "489", "490", "491", "492", "493", "494", "495", "496", "497", "498", "499", "500", 
		"501", "502", "503", "504", "505", "506", "507", "508", "509", "510", "511", "512", "513", "514", "515", "516", "517", "518", "519", "520", 
		"521", "522", "523", "524", "525", "526", "527", "528", "529", "530", "531", "532", "533", "534", "535", "536", "537", "538", "539", "540", 
		"541", "542", "543", "544", "545", "546", "547", "548", "549", "550", "551", "552", "553", "554", "555", "556", "557", "558", "559", "560", 
		"561", "562", "563", "564", "565", "566", "567", "568", "569", "570", "571", "572", "573", "574", "575", "576", "577", "578", "579", "580", 
		"581", "582", "583", "584", "585", "586", "587", "588", "589", "590", "591", "592", "593", "594", "595", "596", "597", "598", "599", "600", 
		"601", "602", "603", "604", "605", "606", "607", "608", "609", "610", "611", "612", "613", "614", "615", "616", "617", "618", "619", "620", 
		"621", "622", "623", "624", "625", "626", "627", "628", "629", "630", "631", "632", "633", "634", "635", "636", "637", "638", "639", "640", 
		"641", "642", "643", "644", "645", "646", "647", "648", "649", "650", "651", "652", "653", "654", "655", "656", "657", "658", "659", "660", 
		"661", "662", "663", "664", "665", "666", "667", "668", "669", "670", "671", "672", "673", "674", "675", "676", "677", "678", "679", "680", 
		"681", "682", "683", "684", "685", "686", "687", "688", "689", "690", "691", "692", "693", "694", "695", "696", "697", "698", "699", "700", 
		"701", "702", "703", "704", "705", "706", "707", "708", "709", "710", "711", "712", "713", "714", "715", "716", "717", "718", "719", "720" 
		});
	NME_SUBTITLE("Навигация");
	NME_FUNC_BUTTON("Подтвердить выдачу", [](){
		if (((MenuElementChoice *)(documentGivingMenu->getElements()[2]))->getOptions().size()&& ((MenuElementChoice *)(documentGivingMenu->getElements()[3]))->getOptions().size())
		{
			for (auto reader_it : Reader::getBinder().getRecords())
			{
				if (reader_it->getId() == stoi(((MenuElementChoice *)(documentGivingMenu->getElements()[2]))->getChoice()))
				{
					for (auto document_it : Document::getBinder().getRecords())
					{
						if (document_it->getId() == stoi(((MenuElementChoice *)(documentGivingMenu->getElements()[3]))->getChoice()))
						{
							DocumentUseRecord::getBinder().getRecords().push_back(new DocumentUseRecord(
								document_it,
								reader_it,
								time(0),
								stoi(((MenuElementChoice *)(documentGivingMenu->getElements()[4]))->getChoice())
							));
						}
					}
				}
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
	initAuthorAddMenu();
	initDocumentAddMenu();
	initReaderAddMenu();
	initPublisherAddMenu();
	initUserAddMenu();
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