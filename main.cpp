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
	// Подготавливаем консоль
	//Utils::setupResolution();
	Utils::setupEncoding();
	menuInitAll();
	User::getBinder().loadRecords();
	User::getBinderUnconfirmed().loadRecords();
	IDBI(Publisher);
	IDBI(Document);
	IDBI(Author);
	IDBI(Reader);
	DocumentAuthorBind::getBinder().loadRecords();
	DocumentUseRecord::getBinder().loadRecords();
	Menu::run();
	cout << "Выход из программы..." << endl;
}
