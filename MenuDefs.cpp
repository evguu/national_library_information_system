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
#include "LockCoutHelper.h"
#include <algorithm>
#include "Log.h"
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
	NME_TITLE("���� � �������");
	NME_SUBTITLE("���� ������");
	CH_NME_EDIT_FIELD("�����", User, LOGIN);
	CH_NME_EDIT_FIELD_H("������", User, PASSWORD);
	NME_SUBTITLE("���������");
	NME_FUNC_BUTTON("�����", []() {
		CH_INIT;
		CH_MOVE(2);
		CH_GET_AS_EF_AND_CHECK(User, LOGIN, login);
		CH_MOVE(1);
		CH_GET_AS_EF_AND_CHECK(User, PASSWORD, password);
		ELK;
		User::loginUser(login, password);
		EULK;
		if (User::getActiveUser())
		{
			loginMenu->reset();
			Menu::multiPopMenuStack(1);
			if (User::getActiveUser()->getIsAdmin())
			{
				adminMenu->addToStack();
				addLog("����� ������������� " + User::getActiveUser()->getLogin());
			}
			else
			{
				userMenu->addToStack();
				addLog("����� ������������ " + User::getActiveUser()->getLogin());
			}
		}
	});
	NME_FUNC_BUTTON("������", []() {
		loginMenu->reset();
		Menu::multiPopMenuStack(1);
	});
	MI_END;
}

// FINISHED
void initRegisterMenu()
{
	MI_START(registerMenu);
	NME_TITLE("�����������");
	NME_SUBTITLE("���� ������");
	CH_NME_EDIT_FIELD("���", Person, FULL_NAME);
	CH_NME_EDIT_FIELD("�����", User, LOGIN);
	CH_NME_EDIT_FIELD_H("������", User, PASSWORD);
	CH_NME_EDIT_FIELD_H("��������� ������", User, PASSWORD);
	NME_SUBTITLE("���������");
	NME_FUNC_BUTTON("������������������", []() {
		CH_INIT;
		CH_MOVE(2);
		CH_GET_AS_EF_AND_CHECK(Person, FULL_NAME, fullName);
		CH_MOVE(1);
		CH_GET_AS_EF_AND_CHECK(User, LOGIN, login);
		CH_MOVE(1);
		CH_GET_AS_EF_AND_CHECK(User, PASSWORD, password);
		CH_MOVE(1);
		CH_GET_AS_EF_AND_CHECK(User, PASSWORD, repeatPassword);
		ELK;
		if (User::registerUser(fullName, login, password, repeatPassword))
		{
			registerMenu->reset();
			Menu::multiPopMenuStack(1);
		}
		EULK;
	});
	NME_FUNC_BUTTON("������", []() {
		registerMenu->reset();
		Menu::multiPopMenuStack(1);
	});
	MI_END;
}

// FINISHED
void initUserMenu()
{
	MI_START(userMenu);
	NME_TITLE("���� ������������");
	NME_SUBTITLE("������");
	NME_FUNC_BUTTON("�������� � �������", []() { dataTypeMenu->addToStack(); });
	NME_FUNC_BUTTON("������ ��������", []() { initDocumentGivingMenu(); documentGivingMenu->addToStack(); });
	NME_FUNC_BUTTON("����������� ������������� ��������", []() { initReaderDebtListMenu(); readerDebtListMenu->addToStack(); });
	NME_SUBTITLE("���������");
	NME_FUNC_BUTTON("�����", []() {
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
	NME_TITLE("���� ��������������");
	NME_SUBTITLE("����������");
	NME_FUNC_BUTTON("�������� � �������", []() { dataTypeMenu->addToStack(); });
	NME_FUNC_BUTTON("�������� � ��������������", []() { initUserListMenu(); userListMenu->addToStack(); });
	NME_FUNC_BUTTON("������� �� �����������", []() { initRegisterConfirmationMenu(); registerConfirmationMenu->addToStack(); });
	NME_FUNC_BUTTON("�������� �����", []() { initLogMenu(); logMenu->addToStack(); });
	NME_SUBTITLE("���������");
	NME_FUNC_BUTTON("�����", []() {
		adminMenu->reset();
		User::getActiveUser() = nullptr;
		Menu::multiPopMenuStack(1);
	});
	MI_END;
}

vector<string> colorThemes = {"0F", "07", "87", "78", "70", "F0"};
int chosenTheme = 4;

// FINISHED
void initStartMenu()
{
	system(("color " + colorThemes[chosenTheme]).c_str());
	MI_START(startMenu);
	NME_TITLE("�������������� ������� ������������ ����������");
	NME_SUBTITLE("�����������");
	NME_FUNC_BUTTON("�����", []() { loginMenu->addToStack(); });
	NME_FUNC_BUTTON("������������������", []() { registerMenu->addToStack(); });
	NME_SUBTITLE("���������");
	NME_FUNC_BUTTON("����������� ����", []() { 
		chosenTheme++; 
		chosenTheme %= colorThemes.size();
		system(("color " + colorThemes[chosenTheme]).c_str());
	});
	NME_FUNC_BUTTON("����� �� ���������", []() { Menu::finish(); });
	MI_END;
}

// FINISHED
void initDataTypeMenu()
{
	MI_START(dataTypeMenu);
	NME_TITLE("����� ���� ������");
	NME_SUBTITLE("����");
	NME_FUNC_BUTTON("������", []() { initAuthorListMenu(); authorListMenu->addToStack(); });
	NME_FUNC_BUTTON("��������", []() { initReaderListMenu(); readerListMenu->addToStack(); });
	NME_FUNC_BUTTON("���������", []() { initDocumentListMenu(); documentListMenu->addToStack(); });
	NME_FUNC_BUTTON("��������", []() { initPublisherListMenu(); publisherListMenu->addToStack(); });
	NME_SUBTITLE("���������");
	NME_FUNC_BUTTON("�����", []() { 
		dataTypeMenu->reset(); 
		Menu::multiPopMenuStack(1);
	});
	MI_END;
}

// FINISHED
void initRegisterConfirmationMenu()
{
	MI_START(registerConfirmationMenu);
	NME_TITLE("������� �� �����������");
	NME_SUBTITLE("���������������� �������");
	for (auto it : User::getBinderUnconfirmed().getRecords())
	{
		NME_CHOICE("���: " + it->getFullName() + ", �����: " + it->getLogin(), {"�������� ����������������", "����������� �����������", "��������� �����������"});
	}
	NME_SUBTITLE("���������");
	NME_FUNC_BUTTON("���������", []() {
		auto elemIt = registerConfirmationMenu->getElements().begin();
		elemIt += 2;
		int offset = 0;
		int size = User::getBinderUnconfirmed().getRecords().size();
		for (int i = 0; i < size; ++i)
		{
			if (((MenuElementChoice*)(*elemIt))->getChoice() == "����������� �����������")
			{
				User::getBinder().getRecords().push_back(User::getBinderUnconfirmed().getRecords()[i-offset]);
				User::getBinderUnconfirmed().getRecords().erase(User::getBinderUnconfirmed().getRecords().begin()+i-offset);
				++offset;
				addLog("�������� ����������� ������������ " + User::getBinder().getRecords().back()->getLogin());
			}
			else if (((MenuElementChoice*)(*elemIt))->getChoice() == "��������� �����������")
			{
				User::getBinderUnconfirmed().getRecords().erase(User::getBinderUnconfirmed().getRecords().begin() + i - offset);
				++offset;
				addLog("��������� ����������� ������������ " + User::getBinder().getRecords().back()->getLogin());
			}
			++elemIt;
		}
		User::getBinder().saveRecords();
		User::getBinderUnconfirmed().saveRecords();
		registerConfirmationMenu->reset();
		Menu::multiPopMenuStack(1);
	});
	NME_FUNC_BUTTON("�����", []() {
		registerConfirmationMenu->reset();
		Menu::multiPopMenuStack(1);
	});
	MI_END;
}

// FINISHED
void initAuthorListMenu()
{
	MI_START(authorListMenu);
	NME_TITLE("������ �������");
	NME_SUBTITLE("������");
	for (auto it : Author::getBinder().getRecords())
	{
		NME_FUNC_BUTTON(to_string(it->getId()) + ". " + it->getFullName(), []() { initAuthorEditMenu(); authorEditMenu->addToStack(); });
	}
	NME_SUBTITLE("���������� � �����");
	CH_NME_EDIT_FIELD_S("�������� � ���", Person, FULL_NAME);
	NME_CHOICE("����������� ��", {"ID", "���"});
	NME_FUNC_BUTTON("������� ���������", []() {
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
		ELK;
		ofstream fout;
		fout.open("report.txt", ios::out);
		for (auto it : sorted)
		{
			if (it->getFullName().find(t1) != string::npos)
			{
				cout << it->str() << endl;
				fout << it->str() << endl;
			}
		}
		fout.close();
		EULK;
	});
	NME_SUBTITLE("���������");
	NME_FUNC_BUTTON("�������� ������", []() { authorAddMenu->addToStack(); });
	NME_FUNC_BUTTON("�����", []() {
		authorListMenu->reset();
		Menu::multiPopMenuStack(1);
	});
	MI_END;
}

// FINISHED
void initDocumentListMenu()
{
	MI_START(documentListMenu);
	NME_TITLE("������ ����������");
	NME_SUBTITLE("������");
	for (auto it : Document::getBinder().getRecords())
	{
		NME_FUNC_BUTTON(it->str(), []() { initDocumentEditMenu(); documentEditMenu->addToStack(); });
	}
	NME_SUBTITLE("��������� �������������");
	CH_NME_EDIT_FIELD_S("�������� � ���������", Document, TITLE);
	CH_NME_EDIT_FIELD_S("�������� � �������� ��������", Publisher, NAME);
	NME_CHOICE("����������� ��", { "ID", "���������", "��������" });
	NME_FUNC_BUTTON("������� ���������", []() {
		vector<Document*>sorted(Document::getBinder().getRecords());
		CH_INIT;
		CH_MOVE(3 + Document::getBinder().getRecords().size());
		string t1 = CH_GET_AS(MenuElementEditField)->getInput();
		CH_MOVE(1);
		string t2 = CH_GET_AS(MenuElementEditField)->getInput();
		CH_MOVE(1);
		int t3 = CH_GET_AS(MenuElementChoice)->getActiveOption();
		if (t3 == 0)
		{
			sort(sorted.begin(), sorted.end(), [](Document *e1, Document* e2) {
				return e1->getId() < e2->getId();
			});
		}
		else if (t3 == 1)
		{
			sort(sorted.begin(), sorted.end(), [](Document *e1, Document* e2) {
				return e1->getTitle() < e2->getTitle();
			});
		}
		else if (t3 == 2)
		{
			sort(sorted.begin(), sorted.end(), [](Document *e1, Document* e2) {
				return e1->getPublisher()->getName() < e2->getPublisher()->getName();
			});
		}
		ELK;
		ofstream fout;
		fout.open("report.txt", ios::out);
		for (auto it : sorted)
		{
			if ((it->getTitle().find(t1) != string::npos)&& (it->getPublisher()->getName().find(t2) != string::npos))
			{
				cout << it->str() << endl;
				fout << it->str() << endl;
			}
		}
		fout.close();
		EULK;
	});
	NME_SUBTITLE("���������");
	NME_FUNC_BUTTON("�������� ��������", []() { initDocumentAddMenu(); documentAddMenu->addToStack(); });
	NME_FUNC_BUTTON("�����", []() {
		documentListMenu->reset();
		Menu::multiPopMenuStack(1);
	});
	MI_END;
}

// FINISHED
void initReaderListMenu()
{
	MI_START(readerListMenu);
	NME_TITLE("������ ���������");
	NME_SUBTITLE("������");
	for (auto it : Reader::getBinder().getRecords())
	{
		NME_FUNC_BUTTON(it->str(), []() { initReaderEditMenu(); readerEditMenu->addToStack(); });
	}
	NME_SUBTITLE("��������� �������������");
	CH_NME_EDIT_FIELD_S("�������� � �����", Person, FULL_NAME);
	NME_CHOICE("����������� ��", { "ID", "�����"});
	NME_FUNC_BUTTON("������� ���������", []() {
		vector<Reader*>sorted(Reader::getBinder().getRecords());
		CH_INIT;
		CH_MOVE(3 + Reader::getBinder().getRecords().size());
		string t1 = CH_GET_AS(MenuElementEditField)->getInput();
		CH_MOVE(1);
		int t2 = CH_GET_AS(MenuElementChoice)->getActiveOption();
		if (t2 == 0)
		{
			sort(sorted.begin(), sorted.end(), [](Reader *e1, Reader* e2) {
				return e1->getId() < e2->getId();
			});
		}
		else if (t2 == 1)
		{
			sort(sorted.begin(), sorted.end(), [](Reader *e1, Reader* e2) {
				return e1->getFullName() < e2->getFullName();
			});
		}
		ELK;
		ofstream fout;
		fout.open("report.txt", ios::out);
		for (auto it : sorted)
		{
			if (it->getFullName().find(t1) != string::npos)
			{
				cout << it->str() << endl;
				fout << it->str() << endl;
			}
		}
		fout.close();
		EULK;
	});
	NME_SUBTITLE("���������");
	NME_FUNC_BUTTON("�������� ��������", []() { readerAddMenu->addToStack(); });
	NME_FUNC_BUTTON("�����", []() {
		readerListMenu->reset();
		Menu::multiPopMenuStack(1);
	});
	MI_END;
}

// FINISHED
void initPublisherListMenu()
{
	MI_START(publisherListMenu);
	NME_TITLE("������ ���������");
	NME_SUBTITLE("������");
	for (auto it : Publisher::getBinder().getRecords())
	{
		NME_FUNC_BUTTON(to_string(it->getId()) + ". " + it->getName(), []() { initPublisherEditMenu(); publisherEditMenu->addToStack(); });
	}
	NME_SUBTITLE("��������� �������������");
	CH_NME_EDIT_FIELD_S("�������� � ��������", Publisher, NAME);
	NME_CHOICE("����������� ��", { "ID", "��������" });
	NME_FUNC_BUTTON("������� ���������", []() {
		vector<Publisher*>sorted(Publisher::getBinder().getRecords());
		CH_INIT;
		CH_MOVE(3 + Publisher::getBinder().getRecords().size());
		string t1 = CH_GET_AS(MenuElementEditField)->getInput();
		CH_MOVE(1);
		int t2 = CH_GET_AS(MenuElementChoice)->getActiveOption();
		if (t2 == 0)
		{
			sort(sorted.begin(), sorted.end(), [](Publisher *e1, Publisher* e2) {
				return e1->getId() < e2->getId();
			});
		}
		else if (t2 == 1)
		{
			sort(sorted.begin(), sorted.end(), [](Publisher *e1, Publisher* e2) {
				return e1->getName() < e2->getName();
			});
		}
		ELK;
		ofstream fout;
		fout.open("report.txt", ios::out);
		for (auto it : sorted)
		{
			if (it->getName().find(t1) != string::npos)
			{
				cout << it->str() << endl;
				fout << it->str() << endl;
			}
		}
		fout.close();
		EULK;
	});
	NME_SUBTITLE("���������");
	NME_FUNC_BUTTON("�������� ��������", []() { publisherAddMenu->addToStack(); });
	NME_FUNC_BUTTON("�����", []() {
		publisherListMenu->reset();
		Menu::multiPopMenuStack(1);
	});
	MI_END;
}

// FINISHED
void initUserListMenu()
{
	MI_START(userListMenu);
	NME_TITLE("������ �������������");
	NME_SUBTITLE("������");
	for (auto it : User::getBinder().getRecords())
	{
		NME_FUNC_BUTTON(it->getLogin() + ". " + it->getFullName(), []() { initUserEditMenu(); userEditMenu->addToStack(); });
	}
	NME_SUBTITLE("���������");
	NME_FUNC_BUTTON("�������� ������������", []() { userAddMenu->addToStack(); });
	NME_FUNC_BUTTON("�����", []() {
		userListMenu->reset();
		Menu::multiPopMenuStack(1);
	});
	MI_END;
}

// FINISHED
void initAuthorAddMenu()
{
	MI_START(authorAddMenu);
	NME_TITLE("�������� ������");
	NME_SUBTITLE("������");
	CH_NME_EDIT_FIELD("���", Person, FULL_NAME);
	NME_SUBTITLE("���������");
	NME_FUNC_BUTTON("��������", []() {
		CH_INIT;
		CH_MOVE(2);
		CH_GET_AS_EF_AND_CHECK(Person, FULL_NAME, fullName);
		Author::getBinder().getRecords().push_back(new Author(fullName));
		Author::getBinder().saveRecords();
		addLog("�������� ����� " + Author::getBinder().getRecords().back()->str());
		ELK;
		cout << "���������� �������." << endl;
		EULK;
		authorAddMenu->reset();
		Menu::multiPopMenuStack(2);
		initAuthorListMenu();
		authorListMenu->addToStack();
	});
	NME_FUNC_BUTTON("������", []() {
		authorAddMenu->reset();
		Menu::multiPopMenuStack(1);
	});
	MI_END;
}

// FINISHED
void initDocumentAddMenu()
{
	MI_START(documentAddMenu);
	NME_TITLE("�������� ��������");
	NME_SUBTITLE("������");
	CH_NME_EDIT_FIELD("��������", Document, TITLE);
	NME_CHOICE("��� ���������", Document::types);
	NME_CHOICE("����", Document::languages);
	vector<string> publishers;
	for (auto it : Publisher::getBinder().getRecords())
	{
		publishers.push_back(it-> str());
	}
	NME_CHOICE("��������", publishers);
	NME_CHOICE("����� �������", 1, 2001);
	NME_SUBTITLE("���������");
	NME_FUNC_BUTTON("��������", []() {
		if (!Publisher::getBinder().getRecords().size())
		{
			ELK;
			cout << "���������� ����������� -- ������ ��������� ����!" << endl;
			EULK;
			return;
		}
		CH_INIT;
		CH_MOVE(2);
		CH_GET_AS_EF_AND_CHECK(Document, TITLE, title);
		CH_MOVE(1);
		int type = ((MenuElementChoice *)(*it))->getActiveOption();
		CH_MOVE(1);
		int language = ((MenuElementChoice *)(*it))->getActiveOption();
		CH_MOVE(1);
		int publisherId = Publisher::getBinder().getRecords()[((MenuElementChoice *)(*it))->getActiveOption()]->getId();
		CH_MOVE(1);
		int pageCount = stoi(((MenuElementChoice *)(*it))->getChoice());
		for (auto it : Publisher::getBinder().getRecords())
		{
			if (it->getId() == publisherId)
			{
				Document::getBinder().getRecords().push_back(new Document((Document::Type)type, (Document::Language)language, it, title, pageCount));
				break;
			}
		}
		Document::getBinder().saveRecords();
		addLog("�������� �������� " + Document::getBinder().getRecords().back()->str());
		ELK;
		cout << "���������� �������." << endl;
		EULK;
		documentAddMenu->reset();
		Menu::multiPopMenuStack(2);
		initDocumentListMenu();
		documentListMenu->addToStack();
	});
	NME_FUNC_BUTTON("������", []() {
		documentAddMenu->reset();
		Menu::multiPopMenuStack(1);
	});
	MI_END;
}

// FINISHED
void initReaderAddMenu()
{
	MI_START(readerAddMenu);
	NME_TITLE("�������� ��������");
	NME_SUBTITLE("������");
	CH_NME_EDIT_FIELD("���", Person, FULL_NAME);
	CH_NME_EDIT_FIELD("����� ��������", Reader, PHONE_NUMBER);
	CH_NME_EDIT_FIELD("�����", Reader, ADDRESS);
	CH_NME_EDIT_FIELD("�� ��������", Reader, PASSPORT_ID);
	NME_SUBTITLE("���������");
	NME_FUNC_BUTTON("��������", []() {
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
		addLog("�������� �������� " + Reader::getBinder().getRecords().back()->str());
		Reader::getBinder().saveRecords();
		readerAddMenu->reset();
		Menu::multiPopMenuStack(2);
		initReaderListMenu();
		readerListMenu->addToStack();
	});
	NME_FUNC_BUTTON("������", []() {
		readerAddMenu->reset();
		Menu::multiPopMenuStack(1);
	});
	MI_END;
}

// FINISHED
void initPublisherAddMenu()
{
	MI_START(publisherAddMenu);
	NME_TITLE("�������� ��������");
	NME_SUBTITLE("������");
	CH_NME_EDIT_FIELD("��������", Publisher, NAME);
	NME_SUBTITLE("���������");
	NME_FUNC_BUTTON("��������", []() {
		CH_INIT;
		CH_MOVE(2);
		CH_GET_AS_EF_AND_CHECK(Publisher, NAME, name);
		addLog("�������� �������� " + Publisher::getBinder().getRecords().back()->str());
		Publisher::getBinder().getRecords().push_back(new Publisher(name));
		Publisher::getBinder().saveRecords();
		publisherAddMenu->reset();
		Menu::multiPopMenuStack(2);
		initPublisherListMenu();
		publisherListMenu->addToStack();
	});
	NME_FUNC_BUTTON("������", []() {
		publisherAddMenu->reset();
		Menu::multiPopMenuStack(1);
	});
	MI_END;
}

// FINISHED
void initUserAddMenu()
{
	MI_START(userAddMenu);
	NME_TITLE("�������� ������������");
	NME_SUBTITLE("������");
	CH_NME_EDIT_FIELD("���", Person, FULL_NAME);
	CH_NME_EDIT_FIELD("�����", User, LOGIN);
	CH_NME_EDIT_FIELD_H("������", User, PASSWORD);
	CH_NME_EDIT_FIELD_H("��������� ������", User, PASSWORD);
	NME_SUBTITLE("���������");
	NME_FUNC_BUTTON("����������������", []() {
		CH_INIT;
		CH_MOVE(2);
		CH_GET_AS_EF_AND_CHECK(Person, FULL_NAME, fullName);
		CH_MOVE(1);
		CH_GET_AS_EF_AND_CHECK(User, LOGIN, login);
		CH_MOVE(1);
		CH_GET_AS_EF_AND_CHECK(User, PASSWORD, password);
		CH_MOVE(1);
		CH_GET_AS_EF_AND_CHECK(User, PASSWORD, repeatPassword);
		ELK;
		if (User::registerUser(fullName, login, password, repeatPassword, true))
		{
			addLog("�������� ������������ " + User::getBinder().getRecords().back()->getLogin());
			userAddMenu->reset();
			Menu::multiPopMenuStack(2);
			initUserListMenu();
			userListMenu->addToStack();
		}
		EULK;
	});
	NME_FUNC_BUTTON("������", []() {
		userAddMenu->reset();
		Menu::multiPopMenuStack(1);
	});
	MI_END;
}

// FINISHED
void initAuthorEditMenu()
{
	MI_START(authorEditMenu);
	NME_TITLE("������������� ������");
	NME_SUBTITLE("������");
	CH_NME_EDIT_FIELD("���", Person, FULL_NAME);
	GET_CTX(Author, author, 2);
	((MenuElementEditField *)ME_PREV)->getInput() = ctx->getFullName();
	NME_SUBTITLE("������� ����");
	DOOM_BUTTON(Author, author);
	NME_SUBTITLE("���������");
	NME_FUNC_BUTTON("���������", []() {
		CH_INIT;
		CH_MOVE(2);
		CH_GET_AS_EF_AND_CHECK(Person, FULL_NAME, fullName);
		GET_CTX(Author, author, 2);
		ctx->getFullName() = CH_GET_AS(MenuElementEditField)->getInput();
		Author::getBinder().saveRecords();
		addLog("������� ����� " + ctx->str());
		ELK;
		cout << "��������� �������." << endl;
		EULK;
		Menu::multiPopMenuStack(2);
		initAuthorListMenu();
		authorListMenu->addToStack();
	});
	NME_FUNC_BUTTON("������", []() {
		Menu::multiPopMenuStack(1);
	});
	MI_END;
}

vector<DocumentUseRecord *> _documentEditMenu_r1;
vector<DocumentAuthorBind *> _documentEditMenu_r2;
vector<Author *> _documentEditMenu_r3;

// FINISHED
void initDocumentEditMenu()
{
	GET_CTX(Document, document, 2);
	MI_START(documentEditMenu);
	NME_TITLE("������������� ��������"); // 0
	DocumentUseRecord::searchByDocumentId(ctx->getId(), _documentEditMenu_r1);
	if (_documentEditMenu_r1.size())
	{
		NME_SUBTITLE("��������� ������ � ������: " + _documentEditMenu_r1.back()->str(true)); // 1
	}
	else
	{
		NME_SUBTITLE("��� ������� � ������"); // 1
	}
	NME_SUBTITLE("������"); // 2
	DocumentAuthorBind::searchByDocumentId(ctx->getId(), _documentEditMenu_r2);
	for (auto it : _documentEditMenu_r2)
	{
		NME_CHOICE(it->getAuthor()->str(), {"��������", "�������"}); // 2 + [1..results2.size()]
	}
	NME_SUBTITLE("������"); // 3 + results2.size()
	CH_NME_EDIT_FIELD("��������", Document, TITLE); // 4 + results2.size()
	((MenuElementEditField *)ME_PREV)->getInput() = ctx->getTitle();
	NME_CHOICE("��� ���������", Document::types);	// 5 + results2.size()
	((MenuElementChoice *)ME_PREV)->getActiveOption() = (int)ctx->getType();
	NME_CHOICE("����", Document::languages); // 6 + results2.size()
	((MenuElementChoice *)ME_PREV)->getActiveOption() = (int)ctx->getLanguage();
	vector<string> publishers;
	for (auto it : Publisher::getBinder().getRecords())
	{
		publishers.push_back(it->str());
	}
	NME_CHOICE("��������", publishers); // 7 + results2.size()
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
	NME_CHOICE("����� �������", 1, 2001); // 8 + results2.size()
	((MenuElementChoice *)ME_PREV)->getActiveOption() = ctx->getPageCount() - 1;
	NME_SUBTITLE("���������� �������"); // 9 + results2.size()
	DocumentAuthorBind::unsearchByRelatedBinds(_documentEditMenu_r3, _documentEditMenu_r2);
	for (auto it : _documentEditMenu_r3)
	{
		NME_CHOICE(it->str(), { "�� �������� �������", "�������� � ������ �������" }); // 9 + results2.size() + [1..results3.size()]
	}
	NME_SUBTITLE("������� ����");
	DOOM_BUTTON(Document, document);
	NME_SUBTITLE("���������");
	NME_FUNC_BUTTON("��������� ���������", []() {
		GET_CTX(Document, document, 2);
		CH_INIT;
		CH_MOVE(_documentEditMenu_r2.size() + 4);
		CH_GET_AS_EF_AND_CHECK(Document, TITLE, title);
		CH_MOVE(1);
		int type = ((MenuElementChoice *)(*it))->getActiveOption();
		CH_MOVE(1);
		int language = ((MenuElementChoice *)(*it))->getActiveOption();
		CH_MOVE(1);
		int publisherId = Publisher::getBinder().getRecords()[((MenuElementChoice *)(*it))->getActiveOption()]->getId();
		CH_MOVE(1);
		int pageCount = stoi(((MenuElementChoice *)(*it))->getChoice());
		for (auto it : Publisher::getBinder().getRecords())
		{
			if (it->getId() == publisherId)
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
		CH_MOVE(2 + _documentEditMenu_r2.size());
		for (int i = _documentEditMenu_r2.size() - 1; i >= 0; --i)
		{
			if (CH_GET_AS(MenuElementChoice)->getActiveOption() == 1)
			{
				DocumentAuthorBind::getBinder().getRecords().erase(DocumentAuthorBind::getBinder().getRecords().begin() + i);
			}
			CH_MOVE(-1);
		}
		it = menuElements.begin();
		CH_MOVE(9 + _documentEditMenu_r2.size());
		for (auto it2 : _documentEditMenu_r3)
		{
			CH_MOVE(1);
			if (CH_GET_AS(MenuElementChoice)->getActiveOption() == 1)
			{
				DocumentAuthorBind::getBinder().getRecords().push_back(new DocumentAuthorBind(ctx, it2));
			}
		}
		DocumentAuthorBind::getBinder().saveRecords();
		addLog("������� �������� " + ctx->str());
		Menu::multiPopMenuStack(2);
		initDocumentListMenu();
		documentListMenu->addToStack();
	});	
	NME_FUNC_BUTTON("������", []() {
		documentEditMenu->reset();
		Menu::multiPopMenuStack(1);
	});
	MI_END;
}

// FINISHED
void initReaderEditMenu()
{
	GET_CTX(Reader, reader, 2);
	MI_START(readerEditMenu);
	NME_TITLE("������������� ��������");
	NME_SUBTITLE("������");
	CH_NME_EDIT_FIELD("���", Person, FULL_NAME);
	((MenuElementEditField *)ME_PREV)->getInput() = ctx->getFullName();
	CH_NME_EDIT_FIELD("����� ��������", Reader, PHONE_NUMBER);
	((MenuElementEditField *)ME_PREV)->getInput() = ctx->getPhoneNumber();
	CH_NME_EDIT_FIELD("�����", Reader, ADDRESS);
	((MenuElementEditField *)ME_PREV)->getInput() = ctx->getAddress();
	CH_NME_EDIT_FIELD("�� ��������", Reader, PASSPORT_ID);
	((MenuElementEditField *)ME_PREV)->getInput() = ctx->getPassportId();
	NME_SUBTITLE("������� ����");
	DOOM_BUTTON(Reader, reader);
	NME_SUBTITLE("���������");
	NME_FUNC_BUTTON("���������", []() {
		CH_INIT;
		CH_MOVE(2);
		CH_GET_AS_EF_AND_CHECK(Person, FULL_NAME, fullName);
		CH_MOVE(1);
		CH_GET_AS_EF_AND_CHECK(Reader, PHONE_NUMBER, phoneNumber);
		CH_MOVE(1);
		CH_GET_AS_EF_AND_CHECK(Reader, ADDRESS, address);
		CH_MOVE(1);
		CH_GET_AS_EF_AND_CHECK(Reader, PASSPORT_ID, passportId);
		GET_CTX(Reader, reader, 2);
		ctx->getFullName() = fullName;
		ctx->getPhoneNumber() = phoneNumber;
		ctx->getAddress() = address;
		ctx->getPassportId() = passportId;
		Reader::getBinder().saveRecords();
		addLog("������� �������� " + ctx->str());
		ELK;
		cout << "��������� �������." << endl;
		EULK;
		Menu::multiPopMenuStack(2);
		initReaderListMenu();
		readerListMenu->addToStack();
	});
	NME_FUNC_BUTTON("������", []() {
		Menu::multiPopMenuStack(1);
	});
	MI_END;
}

// FINISHED
void initPublisherEditMenu()
{
	GET_CTX(Publisher, publisher, 2);
	MI_START(publisherEditMenu);
	NME_TITLE("������������� ��������");
	NME_SUBTITLE("������");
	CH_NME_EDIT_FIELD("��������", Publisher, NAME);
	((MenuElementEditField *)ME_PREV)->getInput() = ctx->getName();
	NME_SUBTITLE("������� ����");
	DOOM_BUTTON_L(Publisher, publisher);
	NME_SUBTITLE("���������");
	NME_FUNC_BUTTON("���������", []() {
		CH_INIT;
		CH_MOVE(2);
		CH_GET_AS_EF_AND_CHECK(Publisher, NAME, name);
		GET_CTX(Publisher, publisher, 2);
		ctx->getName() = name;
		Publisher::getBinder().saveRecords();
		addLog("������� �������� " + ctx->str());
		ELK;
		cout << "��������� �������." << endl;
		EULK;
		Menu::multiPopMenuStack(2);
		initPublisherListMenu();
		publisherListMenu->addToStack();
	});
	NME_FUNC_BUTTON("������", []() {
		Menu::multiPopMenuStack(1);
	});
	MI_END;
}

// FINISHED
void initUserEditMenu()
{
	GET_CTX(User, user, 2);
	MI_START(userEditMenu);
	NME_TITLE("������������� ������������ " + ctx->getLogin());
	if (!ctx->getIsAdmin())
	{
		NME_SUBTITLE("������");
		CH_NME_EDIT_FIELD("���", Person, FULL_NAME);
		((MenuElementEditField *)ME_PREV)->getInput() = ctx->getFullName();
		CH_NME_EDIT_FIELD_H("������", User, PASSWORD);
		CH_NME_EDIT_FIELD_H("��������� ������", User, PASSWORD);
		NME_SUBTITLE("������� ����");
		DOOM_BUTTON(User, user);
		NME_SUBTITLE("���������");
		NME_FUNC_BUTTON("���������", []() {
			CH_INIT;
			CH_MOVE(2);
			CH_GET_AS_EF_AND_CHECK(Person, FULL_NAME, fullName);
			CH_MOVE(1);
			CH_GET_AS_EF_AND_CHECK(User, PASSWORD, password);
			CH_MOVE(1);
			CH_GET_AS_EF_AND_CHECK(User, PASSWORD, repeatPassword);
			GET_CTX(User, user, 2);
			if (password == repeatPassword)
			{
				ctx->getEncryptedPassword() = Utils::encrypt(password);
				ctx->getFullName() = fullName;
			}
			else
			{
				ELK;
				cout << "������ �� ���������." << endl;
				EULK;
				return;
			}
			User::getBinder().saveRecords();
			addLog("������� ������������ " + ctx->getLogin());
			ELK;
			cout << "��������� �������." << endl;
			EULK;
			Menu::multiPopMenuStack(2);
			initUserListMenu();
			userListMenu->addToStack();
		});
	}
	else
	{
		NME_SUBTITLE("�������������� � ��������� �������������� ���������!");
		NME_SUBTITLE("���������");
	}
	NME_FUNC_BUTTON("������", []() {
		Menu::multiPopMenuStack(1);
	});
	MI_END;
}

// FINISHED
void initLogMenu()
{
	MI_START(logMenu);
	NME_TITLE("�������� �����");
	NME_SUBTITLE("������");
	NME_FUNC_BUTTON("����������� ����", []() {
		ELK;
		printLogs(); 
		EULK;
	});
	NME_FUNC_BUTTON("�������� ����", []() {
		ELK;
		clearLogs();
		EULK;
	});
	NME_SUBTITLE("���������");
	NME_FUNC_BUTTON("�����", []() {
		Menu::multiPopMenuStack(1);
	});
	MI_END;
}

// FINISHED
void initDocumentGivingMenu()
{
	MI_START(documentGivingMenu);
	NME_TITLE("������ ����������");
	NME_SUBTITLE("�����");
	vector<string> readers;
	for (auto it : Reader::getBinder().getRecords())
	{
		readers.push_back(it->str());
	}
	NME_CHOICE("��������", readers);
	vector<string> documents;
	for (auto it : Document::getBinder().getRecords())
	{
		documents.push_back(it->str());
	}
	NME_CHOICE("��������", documents);
	NME_CHOICE("������ �� ����� ����� (� �����)", 1, 721);
	NME_SUBTITLE("���������");
	NME_FUNC_BUTTON("����������� ������", [](){
		if ((!Reader::getBinder().getRecords().size())||(!Document::getBinder().getRecords().size()))
		{
			documentGivingMenu->reset();
			Menu::multiPopMenuStack(1);
			return;
		}
		int readerId = Reader::getBinder().getRecords()[((MenuElementChoice *)(documentGivingMenu->getElements()[2]))->getActiveOption()]->getId();
		int documentId = Document::getBinder().getRecords()[((MenuElementChoice *)(documentGivingMenu->getElements()[3]))->getActiveOption()]->getId();;

		for (auto reader_it : Reader::getBinder().getRecords())
		{
			if (reader_it->getId() == readerId)
			{
				for (auto document_it : Document::getBinder().getRecords())
				{
					if (document_it->getId() == documentId)
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
		addLog("����� �������� " + DocumentUseRecord::getBinder().getRecords().back()->getDocument()->str() + " �������� " + DocumentUseRecord::getBinder().getRecords().back()->getReader()->str());
		DocumentUseRecord::getBinder().saveRecords();
		documentGivingMenu->reset();
		Menu::multiPopMenuStack(1);
	});
	NME_FUNC_BUTTON("������", []() {
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
	NME_TITLE("������ ��������������");
	NME_SUBTITLE("����� ��������");
	vector<string> readers;
	for (auto it : Reader::getBinder().getRecords())
	{
		readers.push_back(it->str());
	}
	NME_CHOICE("��������", readers);
	if (_readerDebtListMenu_chosenReaderVectorIndex != -1)
	{
		((MenuElementChoice *)(ME_PREV))->getActiveOption() = _readerDebtListMenu_chosenReaderVectorIndex;
	}
	NME_FUNC_BUTTON("������� �������� ��� ���������� ������", []() {
		if (((MenuElementChoice *)(readerDebtListMenu->getElements()[2]))->getOptions().size())
		{
			_readerDebtListMenu_chosenReaderId = Reader::getBinder().getRecords()[((MenuElementChoice *)(readerDebtListMenu->getElements()[2]))->getActiveOption()]->getId();
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
	NME_FUNC_BUTTON("��������� ������ � ������� ��������", []() {
		if (_readerDebtListMenu_chosenReaderVectorIndex != -1)
		{
			CH_INIT;

			vector<DocumentUseRecord *> tmp;
			vector<int> tmpI;
			int tmpIndex = 0;
			for (auto it : DocumentUseRecord::getBinder().getRecords())
			{
				if (_readerDebtListMenu_chosenReaderId == it->getReader()->getId())
				{
					tmp.push_back(it);
					tmpI.push_back(tmpIndex);
				}
				++tmpIndex;
			}

			CH_MOVE(5 + tmp.size());
			for (int i = tmp.size() - 1; i >= 0; --i)
			{
				if(CH_GET_AS(MenuElementChoice)->getActiveOption() == 1)
				{
					delete tmp[i];
					DocumentUseRecord::getBinder().getRecords().erase(DocumentUseRecord::getBinder().getRecords().begin() + tmpI[i]);
				}
				CH_MOVE(-1);
			}
		}
		DocumentUseRecord::getBinder().saveRecords();
		if (((MenuElementChoice *)(readerDebtListMenu->getElements()[2]))->getOptions().size())
		{
			_readerDebtListMenu_chosenReaderId = Reader::getBinder().getRecords()[((MenuElementChoice *)(readerDebtListMenu->getElements()[2]))->getActiveOption()]->getId();
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
		NME_SUBTITLE("�������� �� ������. �������� �������� � ����������� �����.");
	}
	else
	{
		NME_SUBTITLE("������������� ��������");
		for (auto it : DocumentUseRecord::getBinder().getRecords())
		{
			if (_readerDebtListMenu_chosenReaderId == it->getReader()->getId())
			{
				tm ltm;
				time_t tt = it->getGivenAt();
				localtime_s(&ltm, &tt);
				std::stringstream date;
				date << ltm.tm_mday << "/" << ((1 + ltm.tm_mon >= 10) ? ("") : ("0")) << 1 + ltm.tm_mon << "/"
					<< 1900 + ltm.tm_year << " " << ((ltm.tm_hour >= 10) ? ("") : ("0")) << ltm.tm_hour
					<< ":" << ((ltm.tm_min >= 10) ? ("") : ("0")) << ltm.tm_min
					<< ":" << ((ltm.tm_sec >= 10) ? ("") : ("0")) << ltm.tm_sec;
				NME_CHOICE("{" + date.str() + " �� " + to_string(it->getGivenFor()) + " ����� } " + it->getDocument()->getTitle() + " [" + it->getDocument()->getPublisher()->getName() + "]", { "��� ���������", "������� �������������" });
			}
		}
	}
	NME_SUBTITLE("���������");
	NME_FUNC_BUTTON("��������� � �����", []() {
		if (_readerDebtListMenu_chosenReaderVectorIndex != -1)
		{
			CH_INIT;

			vector<DocumentUseRecord *> tmp;
			vector<int> tmpI;
			int tmpIndex = 0;
			for (auto it : DocumentUseRecord::getBinder().getRecords())
			{
				if (_readerDebtListMenu_chosenReaderId == it->getReader()->getId())
				{
					tmp.push_back(it);
					tmpI.push_back(tmpIndex);
				}
				++tmpIndex;
			}

			CH_MOVE(5 + tmp.size());
			for (int i = tmp.size() - 1; i >= 0; --i)
			{
				if (CH_GET_AS(MenuElementChoice)->getActiveOption() == 1)
				{
					delete tmp[i];
					DocumentUseRecord::getBinder().getRecords().erase(DocumentUseRecord::getBinder().getRecords().begin() + tmpI[i]);
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
	NME_FUNC_BUTTON("������", []() {
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
