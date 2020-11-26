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

void initLoginMenu()
{
	MI_START(loginMenu);
	NME_TITLE("���� � �������");
	NME_SUBTITLE("���� ������");
	NME_EDIT_FIELD("�����", false, Constraints::User::LOGIN_ALLOWED_CHARS, Constraints::User::LOGIN_MAX_LENGTH);
	NME_EDIT_FIELD("������", true, Constraints::User::PASSWORD_ALLOWED_CHARS, Constraints::User::PASSWORD_MAX_LENGTH);
	NME_SUBTITLE("���������");
	NME_FUNC_BUTTON("�����", []() {
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
	NME_FUNC_BUTTON("������", []() {
		loginMenu->reset();
		Menu::multiPopMenuStack(1);
	});
	MI_END;
}

void initRegisterMenu()
{
	MI_START(registerMenu);
	NME_TITLE("�����������");
	NME_SUBTITLE("���� ������");
	NME_EDIT_FIELD("���", false, Constraints::Person::FULL_NAME_ALLOWED_CHARS, Constraints::Person::FULL_NAME_MAX_LENGTH);
	NME_EDIT_FIELD("�����", false, Constraints::User::LOGIN_ALLOWED_CHARS, Constraints::User::LOGIN_MAX_LENGTH);
	NME_EDIT_FIELD("������", true, Constraints::User::PASSWORD_ALLOWED_CHARS, Constraints::User::PASSWORD_MAX_LENGTH);
	NME_EDIT_FIELD("��������� ������", true, Constraints::User::PASSWORD_ALLOWED_CHARS, Constraints::User::PASSWORD_MAX_LENGTH);
	NME_SUBTITLE("���������");
	NME_FUNC_BUTTON("������������������", []() {
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
	NME_FUNC_BUTTON("������", []() {
		registerMenu->reset();
		Menu::multiPopMenuStack(1);
	});
	MI_END;
}

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

void initStartMenu()
{
	MI_START(startMenu);
	NME_TITLE("�������������� ������� ������������ ����������");
	NME_SUBTITLE("�����������");
	NME_FUNC_BUTTON("�����", []() {loginMenu->addToStack(); });
	NME_FUNC_BUTTON("������������������", []() {registerMenu->addToStack(); });
	NME_SUBTITLE("���������");
	NME_FUNC_BUTTON("����� �� ���������", []() {isLoopRunning = false; });
	MI_END;
}

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

string _authorListFilterFullName = "";
string _authorListSortBy = "ID";

void initAuthorListMenu()
{
	MI_START(authorListMenu);
	NME_TITLE("������ �������");
	NME_SUBTITLE("������");
	for (auto it : Author::getBinder().getRecords())
	{
		NME_FUNC_BUTTON(to_string(it->getId()) + ". " + it->getFullName(), []() { initAuthorEditMenu(); authorEditMenu->addToStack(); });
	}
	NME_SUBTITLE("��������� �������������");
	NME_EDIT_FIELD("�������� � ���");
	NME_CHOICE("����������� ��", {"ID", "���"});
	NME_FUNC_BUTTON("��������� ���������", []() {
		// TODO
	});
	NME_SUBTITLE("���������");
	NME_FUNC_BUTTON("�������� ������", []() { authorAddMenu->addToStack(); });
	NME_FUNC_BUTTON("�����", []() {
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
	NME_TITLE("������ ����������");
	NME_SUBTITLE("������");
	for (auto it : Document::getBinder().getRecords())
	{
		NME_FUNC_BUTTON(it->str(), []() { initDocumentEditMenu(); documentEditMenu->addToStack(); });
	}
	NME_SUBTITLE("��������� �������������");
	NME_EDIT_FIELD("�������� � ���������");
	NME_EDIT_FIELD("�������� � �������� ��������");
	NME_EDIT_FIELD("�������� � ����� ������");
	NME_CHOICE("����������� ��", { "ID", "���������", "ID ��������", "��������" });
	NME_FUNC_BUTTON("��������� ���������", []() {
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

string _readerListFilterName = "";
string _readerListFilterPassportId = "";
string _readerListSortBy = "ID";

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
	NME_EDIT_FIELD("�������� � �����");
	NME_EDIT_FIELD("�������� � �� ��������");
	NME_CHOICE("����������� ��", { "ID", "�����", "�� ��������" });
	NME_FUNC_BUTTON("��������� ���������", []() {
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

string _publisherListFilterName = "";
string _publisherListSortBy = "ID";

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
	NME_EDIT_FIELD("�������� � ��������");
	NME_CHOICE("����������� ��", { "ID", "��������" });
	NME_FUNC_BUTTON("��������� ���������", []() {
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

string _userListFilterLogin = "";
string _userListFilterFullName = "";
string _userListSortBy = "ID";

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
	NME_EDIT_FIELD("�������� � ������");
	NME_EDIT_FIELD("�������� � ���");
	NME_CHOICE("����������� ��", { "ID", "������", "���" });
	NME_FUNC_BUTTON("��������� ���������", []() {
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

void initAuthorAddMenu()
{
	MI_START(authorAddMenu);
	NME_TITLE("�������� ������");
	NME_SUBTITLE("������");
	NME_EDIT_FIELD("���", false, Constraints::Person::FULL_NAME_ALLOWED_CHARS, Constraints::Person::FULL_NAME_MAX_LENGTH);
	NME_SUBTITLE("���������");
	NME_FUNC_BUTTON("��������", []() {
		auto menuElements = Menu::getActive()->getElements();
		string fullName;
		auto it = menuElements.begin();
		it += 2;
		fullName = ((MenuElementEditField *)(*it))->getInput();
		if (fullName.length() < Constraints::Person::FULL_NAME_MIN_LENGTH)
		{
			cout << "����� ����� �� ����� ���� ������ " << Constraints::Person::FULL_NAME_MIN_LENGTH << " ��������." << endl;
			system("pause");
		}
		else
		{
			Author::getBinder().getRecords().push_back(new Author(fullName));
			Author::getBinder().saveRecords();
			cout << "���������� �������." << endl;
			system("pause");
			authorAddMenu->reset();
			Menu::multiPopMenuStack(2);
			initAuthorListMenu();
			authorListMenu->addToStack();
		}
	});
	NME_FUNC_BUTTON("������", []() {
		authorAddMenu->reset();
		Menu::multiPopMenuStack(1);
	});
	MI_END;
}

void initDocumentAddMenu()
{
	MI_START(documentAddMenu);
	NME_TITLE("�������� ��������");
	NME_SUBTITLE("������");
	NME_EDIT_FIELD("��������", false, Constraints::Document::TITLE_ALLOWED_CHARS, Constraints::Document::TITLE_MAX_LENGTH);
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
		auto menuElements = Menu::getActive()->getElements();
		string title = ((MenuElementEditField *)menuElements[2])->getInput();
		int type = ((MenuElementChoice *)menuElements[3])->getActiveOption();
		int language = ((MenuElementChoice *)menuElements[4])->getActiveOption();
		string publisherId = ((MenuElementChoice *)menuElements[5])->getChoice();
		int pageCount = stoi(((MenuElementChoice *)menuElements[6])->getChoice());
		if (publisherId == MenuElementChoice::noChoicesFoundMessage)
		{
			cout << "���������� ����������� -- ������ ��������� ����!" << endl;
			system("pause");
		}
		else if (title.length() < Constraints::Document::TITLE_MIN_LENGTH)
		{
			cout << "��������� �� ����� ���� ������ " << Constraints::Document::TITLE_MIN_LENGTH << " ��������!" << endl;
			system("pause");
		}
		else
		{
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
		}
	});
	NME_FUNC_BUTTON("������", []() {
		documentAddMenu->reset();
		Menu::multiPopMenuStack(1);
	});
	MI_END;
}

void initReaderAddMenu()
{
	MI_START(readerAddMenu);
	NME_TITLE("�������� ��������");
	NME_SUBTITLE("������");
	NME_EDIT_FIELD("���", false, Constraints::Person::FULL_NAME_ALLOWED_CHARS, Constraints::Person::FULL_NAME_MAX_LENGTH);
	NME_EDIT_FIELD("����� ��������", false, Constraints::Reader::PHONE_NUMBER_ALLOWED_CHARS, Constraints::Reader::PHONE_NUMBER_MAX_LENGTH);
	NME_EDIT_FIELD("�����", false, Constraints::Reader::ADDRESS_ALLOWED_CHARS, Constraints::Reader::ADDRESS_MAX_LENGTH);
	NME_EDIT_FIELD("�� ��������", false, Constraints::Reader::PASSPORT_ID_ALLOWED_CHARS, Constraints::Reader::PASSPORT_ID_MAX_LENGTH);
	NME_SUBTITLE("���������");
	NME_FUNC_BUTTON("��������", []() {
		// TODO
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

void initPublisherAddMenu()
{
	MI_START(publisherAddMenu);
	NME_TITLE("�������� ��������");
	NME_SUBTITLE("������");
	NME_EDIT_FIELD("��������", false, Constraints::Publisher::NAME_ALLOWED_CHARS, Constraints::Publisher::NAME_MAX_LENGTH);
	NME_SUBTITLE("���������");
	NME_FUNC_BUTTON("��������", []() {
		auto menuElements = Menu::getActive()->getElements();
		string name = ((MenuElementEditField *)menuElements[2])->getInput();
		if (name.length() < Constraints::Publisher::NAME_MIN_LENGTH)
		{
			cout << "����� �������� �� ����� ���� ������ " << Constraints::Publisher::NAME_MIN_LENGTH << " ��������." << endl;
			system("pause");
		}
		else
		{
			Publisher::getBinder().getRecords().push_back(new Publisher(name));
			Publisher::getBinder().saveRecords();
			publisherAddMenu->reset();
			Menu::multiPopMenuStack(2);
			initPublisherListMenu();
			publisherListMenu->addToStack();
		}
	});
	NME_FUNC_BUTTON("������", []() {
		publisherAddMenu->reset();
		Menu::multiPopMenuStack(1);
	});
	MI_END;
}

void initUserAddMenu()
{
	MI_START(userAddMenu);
	NME_TITLE("�������� ������������");
	NME_SUBTITLE("������");
	NME_EDIT_FIELD("���", false, Constraints::Person::FULL_NAME_ALLOWED_CHARS, Constraints::Person::FULL_NAME_MAX_LENGTH);
	NME_EDIT_FIELD("�����", false, Constraints::User::LOGIN_ALLOWED_CHARS, Constraints::User::LOGIN_MAX_LENGTH);
	NME_EDIT_FIELD("������", true, Constraints::User::PASSWORD_ALLOWED_CHARS, Constraints::User::PASSWORD_MAX_LENGTH);
	NME_EDIT_FIELD("��������� ������", true, Constraints::User::PASSWORD_ALLOWED_CHARS, Constraints::User::PASSWORD_MAX_LENGTH);
	NME_SUBTITLE("���������");
	NME_FUNC_BUTTON("����������������", []() {
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
	NME_FUNC_BUTTON("������", []() {
		userAddMenu->reset();
		Menu::multiPopMenuStack(1);
	});
	MI_END;
}

void initAuthorEditMenu()
{
	MI_START(authorEditMenu);
	NME_TITLE("������������� ������");
	NME_SUBTITLE("������");
	NME_SUBTITLE("���������");
	NME_FUNC_BUTTON("������", []() {
		Menu::multiPopMenuStack(1);
	});
	MI_END;
}

void initDocumentEditMenu()
{
	GET_CTX(Document, document, 2);
	MI_START(documentEditMenu);
	NME_TITLE("������������� ��������");
	NME_SUBTITLE("������� �������������");
	vector<DocumentUseRecord *> results1;
	DocumentUseRecord::searchByDocumentId(ctx->getId(), results1);
	for (auto it : results1)
	{
		NME_CHOICE(it->str(), {});
	}
	NME_SUBTITLE("������");
	vector<DocumentAuthorBind *> results2;
	DocumentAuthorBind::searchByDocumentId(ctx->getId(), results2);
	for (auto it : results2)
	{
		NME_CHOICE(it->str(), {});
	}
	NME_SUBTITLE("������");
	NME_SUBTITLE("���������");
	NME_FUNC_BUTTON("������", []() {
		Menu::multiPopMenuStack(1);
	});
	MI_END;
}

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

int _chosenReaderIdForDebtListing = -1;

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
	NME_FUNC_BUTTON("������� �������� ��� ���������� ������", []() {
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
	NME_FUNC_BUTTON("��������� ������ � ������� ��������", []() {
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
	NME_SUBTITLE("������������� ��������");
	for (auto it : DocumentUseRecord::getBinder().getRecords())
	{
		if (_chosenReaderIdForDebtListing == it->getReader()->getId())
		{
			NME_CHOICE(it->getDocument()->getTitle() + " [" + it->getDocument()->getPublisher()->getName() + "]", { "��� ���������", "������� �������������" });
		}
	}
	NME_SUBTITLE("���������");
	NME_FUNC_BUTTON("��������� � �����", []() {
		// TODO data save
		DocumentUseRecord::getBinder().saveRecords();
		readerDebtListMenu->reset();
		Menu::multiPopMenuStack(1);
		_chosenReaderIdForDebtListing = -1;
	});
	NME_FUNC_BUTTON("������", []() {
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