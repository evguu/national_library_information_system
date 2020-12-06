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
	Utils::setupResolution();
	Utils::setupEncoding();
	menuInitAll();
	User::getBinder().loadRecords();
	User::getBinderUnconfirmed().loadRecords();
	if (User::getBinder().getRecords().size() == 0)
	{
		User::getBinder().getRecords().push_back(new User("Администратор системы", "admin", Utils::encrypt("admin0"), true));
	}
	IDBI(Publisher);
	IDBI(Document);
	IDBI(Author);
	IDBI(Reader);
	DocumentAuthorBind::getBinder().loadRecords();
	DocumentUseRecord::getBinder().loadRecords();
	Menu::run();
	system("cls");
	cout << "Выход из программы..." << endl;
}
