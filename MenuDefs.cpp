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
		if (User::registerUser(fullName, login, password, repeatPassword))
		{
			registerMenu->reset();
			Menu::multiPopMenuStack(1);
		}
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

// FINISHED
void initStartMenu()
{
	MI_START(startMenu);
	NME_TITLE("�������������� ������� ������������ ����������");
	NME_SUBTITLE("�����������");
	NME_FUNC_BUTTON("�����", []() { loginMenu->addToStack(); });
	NME_FUNC_BUTTON("������������������", []() { registerMenu->addToStack(); });
	NME_SUBTITLE("���������");
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
			}
			else if (((MenuElementChoice*)(*elemIt))->getChoice() == "��������� �����������")
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
	CH_NME_EDIT_FIELD("�������� � ���", Person, FULL_NAME);
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
	NME_SUBTITLE("���������");
	NME_FUNC_BUTTON("�������� ������", []() { authorAddMenu->addToStack(); });
	NME_FUNC_BUTTON("�����", []() {
		authorListMenu->reset();
		Menu::multiPopMenuStack(1);
	});
	MI_END;
}

// TODO
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
	CH_NME_EDIT_FIELD("�������� � ���������", Document, TITLE);
	CH_NME_EDIT_FIELD("�������� � �������� ��������", Publisher, NAME);
	CH_NME_EDIT_FIELD("�������� � ����� ������", Person, FULL_NAME);
	NME_CHOICE("����������� ��", { "ID", "���������", "ID ��������", "��������" });
	NME_FUNC_BUTTON("������� ���������", []() {
		// TODO
	});
	NME_SUBTITLE("���������");
	NME_FUNC_BUTTON("�������� ��������", []() { initDocumentAddMenu(); documentAddMenu->addToStack(); });
	NME_FUNC_BUTTON("�����", []() {
		documentListMenu->reset();
		Menu::multiPopMenuStack(1);
	});
	MI_END;
}

// TODO
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
	CH_NME_EDIT_FIELD("�������� � �����", Person, FULL_NAME);
	CH_NME_EDIT_FIELD("�������� � �� ��������", Reader, PASSPORT_ID);
	NME_CHOICE("����������� ��", { "ID", "�����", "�� ��������" });
	NME_FUNC_BUTTON("������� ���������", []() {
		// TODO
	});
	NME_SUBTITLE("���������");
	NME_FUNC_BUTTON("�������� ��������", []() { readerAddMenu->addToStack(); });
	NME_FUNC_BUTTON("�����", []() {
		readerListMenu->reset();
		Menu::multiPopMenuStack(1);
	});
	MI_END;
}

// TODO
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
	CH_NME_EDIT_FIELD("�������� � ��������", Publisher, NAME);
	NME_CHOICE("����������� ��", { "ID", "��������" });
	NME_FUNC_BUTTON("������� ���������", []() {
		// TODO
	});
	NME_SUBTITLE("���������");
	NME_FUNC_BUTTON("�������� ��������", []() { publisherAddMenu->addToStack(); });
	NME_FUNC_BUTTON("�����", []() {
		publisherListMenu->reset();
		Menu::multiPopMenuStack(1);
	});
	MI_END;
}

// TODO
void initUserListMenu()
{
	MI_START(userListMenu);
	NME_TITLE("������ �������������");
	NME_SUBTITLE("������");
	for (auto it : User::getBinder().getRecords())
	{
		NME_FUNC_BUTTON(it->getLogin() + ". " + it->getFullName(), []() { initUserEditMenu(); userEditMenu->addToStack(); });
	}
	NME_SUBTITLE("��������� �������������");
	CH_NME_EDIT_FIELD("�������� � ������", User, LOGIN);
	CH_NME_EDIT_FIELD("�������� � ���", Person, FULL_NAME);
	NME_CHOICE("����������� ��", { "ID", "������", "���" });
	NME_FUNC_BUTTON("������� ���������", []() {
		// TODO
	});
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
		cout << "���������� �������." << endl;
		system("pause");
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
		publishers.push_back(to_string(it->getId()));
	}
	NME_CHOICE("ID ��������", publishers);
	NME_CHOICE("����� �������", 1, 2001);
	NME_SUBTITLE("���������");
	NME_FUNC_BUTTON("��������", []() {
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
			cout << "���������� ����������� -- ������ ��������� ����!" << endl;
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
		cout << "���������� �������." << endl;
		system("pause");
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
		if (User::registerUser(fullName, login, password, repeatPassword, true))
		{
			userAddMenu->reset();
			Menu::multiPopMenuStack(2);
			initUserListMenu();
			userListMenu->addToStack();
		}
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
	NME_SUBTITLE("���������");
	NME_FUNC_BUTTON("���������", []() {
		CH_INIT;
		CH_MOVE(2);
		CH_GET_AS_EF_AND_CHECK(Person, FULL_NAME, fullName);
		GET_CTX(Author, author, 2);
		ctx->getFullName() = CH_GET_AS(MenuElementEditField)->getInput();
		Author::getBinder().saveRecords();
		cout << "��������� �������." << endl;
		system("pause");
		Menu::multiPopMenuStack(2);
		initAuthorListMenu();
		authorListMenu->addToStack();
	});
	DOOM_BUTTON(Author, author);
	NME_FUNC_BUTTON("������", []() {
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
	NME_TITLE("������������� ��������"); // 0
	DocumentUseRecord::searchByDocumentId(ctx->getId(), results1);
	if (results1.size())
	{
		NME_SUBTITLE("��������� ������ � ������: " + results1.back()->str(true)); // 1
	}
	else
	{
		NME_SUBTITLE("��� ������� � ������"); // 1
	}
	NME_SUBTITLE("������"); // 2
	DocumentAuthorBind::searchByDocumentId(ctx->getId(), results2);
	for (auto it : results2)
	{
		NME_CHOICE(it->str(), {"��������", "�������"}); // 2 + [1..results2.size()]
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
		publishers.push_back(to_string(it->getId()));
	}
	NME_CHOICE("ID ��������", publishers); // 7 + results2.size()
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
	NME_SUBTITLE("������� ����");
	DOOM_BUTTON(Document, document);
	NME_SUBTITLE("���������");
	NME_FUNC_BUTTON("��������� ���������", []() {
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
			cout << "���������� ����������� -- ������ ��������� ����!" << endl;
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
	NME_FUNC_BUTTON("������", []() {
		documentEditMenu->reset();
		Menu::multiPopMenuStack(1);
	});
	MI_END;
}

// TODO
void initReaderEditMenu()
{
	MI_START(readerEditMenu);
	NME_TITLE("������������� ��������");
	NME_SUBTITLE("������");
	NME_SUBTITLE("���������");
	NME_FUNC_BUTTON("������", []() {
		Menu::multiPopMenuStack(1);
	});
	MI_END;
}

// TODO
void initPublisherEditMenu()
{
	MI_START(publisherEditMenu);
	NME_TITLE("������������� ��������");
	NME_SUBTITLE("������");
	NME_SUBTITLE("���������");
	NME_FUNC_BUTTON("������", []() {
		Menu::multiPopMenuStack(1);
	});
	MI_END;
}

// TODO
void initUserEditMenu()
{
	MI_START(userEditMenu);
	NME_TITLE("������������� ������������");
	NME_SUBTITLE("������");
	NME_SUBTITLE("���������");
	NME_FUNC_BUTTON("������", []() {
		Menu::multiPopMenuStack(1);
	});
	MI_END;
}

// TODO
void initLogMenu()
{
	MI_START(logMenu);
	NME_TITLE("�������� �����");
	NME_SUBTITLE("������");
	//TODO ����� ����� ���������� ������ ����������� ������� �����
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
		readers.push_back(to_string(it->getId()));
	}
	NME_CHOICE("ID ��������", readers);
	vector<string> documents;
	for (auto it : Document::getBinder().getRecords())
	{
		documents.push_back(to_string(it->getId()));
	}
	NME_CHOICE("ID ���������", documents);
	NME_CHOICE("������ �� ����� ����� (� �����)", 1, 721);
	NME_SUBTITLE("���������");
	NME_FUNC_BUTTON("����������� ������", [](){
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
		readers.push_back(to_string(it->getId()));
	}
	NME_CHOICE("ID ��������", readers);
	if (_readerDebtListMenu_chosenReaderVectorIndex != -1)
	{
		((MenuElementChoice *)(ME_PREV))->getActiveOption() = _readerDebtListMenu_chosenReaderVectorIndex;
	}
	NME_FUNC_BUTTON("������� �������� ��� ���������� ������", []() {
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
	NME_FUNC_BUTTON("��������� ������ � ������� ��������", []() {
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
		NME_SUBTITLE("�������� �� ������. �������� �������� � ����������� �����.");
	}
	else
	{
		NME_SUBTITLE("������������� ��������");
		for (auto it : DocumentUseRecord::getBinder().getRecords())
		{
			if (_readerDebtListMenu_chosenReaderId == it->getReader()->getId())
			{
				NME_CHOICE(it->getDocument()->getTitle() + " [" + it->getDocument()->getPublisher()->getName() + "]", { "��� ���������", "������� �������������" });
			}
		}
	}
	NME_SUBTITLE("���������");
	NME_FUNC_BUTTON("��������� � �����", []() {
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
