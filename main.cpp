#include "pch.h"
#include <iostream>
#include "Menu.h"
#include "MenuDefs.h"
#include "Console.h"
#include "User.h"
#include "Publisher.h"
#include "Document.h"
#include "Author.h"
#include "Reader.h"
#include "DocumentAuthorBind.h"
#include "DocumentUseRecord.h"
using namespace std;

int main()
{
	// Подготовка консоли
	Utils::setupResolution();
	Utils::setupEncoding();
	//Подготовка меню
	menuInitAll();
	// Загрузка  списка пользователей
	User::getBinder().loadRecords();
	User::getBinderUnconfirmed().loadRecords();
	// Если список пуст, создается администратор
	if (User::getBinder().getRecords().size() == 0)
	{
		User::getBinder().getRecords().push_back(new User("Администратор системы", "admin", Utils::encrypt("admin0"), true));
	}
	// Загрузка списка издателей
	IDBI(Publisher);
	// Загрузка списка документов
	IDBI(Document);
	// Загрузка списка авторов
	IDBI(Author);
	// Загрузка списка читателей
	IDBI(Reader);
	// Загрузка списка связей авторов и документов
	DocumentAuthorBind::getBinder().loadRecords();
	// Загрузка списка задолженностей
	DocumentUseRecord::getBinder().loadRecords();
	// Передача управления менеджеру меню
	Menu::run();
	system("cls");
	cout << "Выход из программы..." << endl;
}
