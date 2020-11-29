#include "pch.h"
#include "User.h"
#include "Encrypt.h"
#include "iostream"
using namespace std;

User* User::activeUser = nullptr;
Utils::FileBindedVector<User> User::binder("users.txt");
Utils::FileBindedVector<User> User::binderUnconfirmed("users_unconfirmed.txt");

namespace Constraints
{
	namespace User
	{
		const int LOGIN_MIN_LENGTH = 4;
		const int LOGIN_MAX_LENGTH = 16;
		const string LOGIN_ALLOWED_CHARS = Constraints::CharacterSets::ENGLISH + Constraints::CharacterSets::NUMBERS + "_";
		const int PASSWORD_MIN_LENGTH = 6;
		const int PASSWORD_MAX_LENGTH = 32;
		const string PASSWORD_ALLOWED_CHARS = Constraints::CharacterSets::ENGLISH + Constraints::CharacterSets::NUMBERS + "_";
	}
};

User* User::loadRecord(ifstream & fin)
{
	string fullName;
	string login;
	string encryptedPassword;
	string isAdmin;
	getline(fin, fullName);
	getline(fin, login);
	getline(fin, encryptedPassword);
	getline(fin, isAdmin);
	if (fin.eof() || fin.fail()) return nullptr;
	return new User(fullName, login, encryptedPassword, isAdmin=="1");
}

void User::saveRecord(ofstream & fout)
{
	fout << getFullName() << endl << login << endl << encryptedPassword << endl << isAdmin << endl;
}

bool User::registerUser(string fullName, string login, string password, string repeatPassword, bool useForce)
{
	bool res;
	if (password != repeatPassword)
	{
		cout << "������ �� ���������." << endl;
		res = false;
	}
	else if (!fullName.length() || !login.length() || !password.length() || !repeatPassword.length())
	{
		cout << "��� ���� ������ ���� ���������." << endl;
		res = false;
	}
	else if (fullName.length() < Constraints::Person::FULL_NAME_MIN_LENGTH)
	{
		cout << "��� �� ����� ���� ������ " << Constraints::Person::FULL_NAME_MIN_LENGTH << " ��������." << endl;
		res = false;
	}
	else if (login.length() < Constraints::User::LOGIN_MIN_LENGTH)
	{
		cout << "����� �� ����� ���� ������ " << Constraints::User::LOGIN_MIN_LENGTH << " ��������." << endl;
		res = false;
	}
	else if (password.length() < Constraints::User::PASSWORD_MIN_LENGTH)
	{
		cout << "������ �� ����� ���� ������ " << Constraints::User::PASSWORD_MIN_LENGTH << " ��������." << endl;
		res = false;
	}
	else
	{
		bool isLoginAlreadyTaken = false;
		for (auto it : binder.getRecords())
		{
			if (login == it->getLogin())
			{
				cout << "����� ��� �����." << endl;
				isLoginAlreadyTaken = true;
				res = false;
				break;
			}
		}
		for (auto it : binderUnconfirmed.getRecords())
		{
			if (isLoginAlreadyTaken) break;
			if (login == it->getLogin())
			{
				cout << "����� ��� ����� ���������������� �������������." << endl;
				isLoginAlreadyTaken = true;
				res = false;
				break;
			}
		}
		if (!isLoginAlreadyTaken)
		{
			if(useForce)
			{
				cout << "������� ������� ���������������." << endl;
				binder.getRecords().push_back(new User(fullName, login, password, false));
				binder.saveRecords();
				res = true;
			}
			else
			{
				cout << "������� ������� ���������������. \n�� ������� ����� ����� ������������� �������� ���������������." << endl;
				binderUnconfirmed.getRecords().push_back(new User(fullName, login, password, false));
				binderUnconfirmed.saveRecords();
				res = true;
			}
		}
	}
	system("pause");
	return res;
}

void User::loginUser(string login, string password)
{
	for (auto it : binder.getRecords())
	{
		if (login == it->login)
		{
			if (Utils::encrypt(password) == it->encryptedPassword)
			{
				activeUser = it;
				cout << "����� ����������, " << it->getFullName() << "!" << endl;
			}
			else
			{
				cout << "������ ��������." << endl;
			}
			system("pause");
			return;
		}
	}
	for (auto it : binderUnconfirmed.getRecords())
	{
		if (login == it->login)
		{
			if (Utils::encrypt(password) == it->encryptedPassword)
			{
				cout << it->getFullName() << ", ��� ������� ������� ������������� ���������������." << endl;
			}
			else
			{
				cout << "������ ��������." << endl;
			}
			system("pause");
			return;
		}
	}
	cout << "������� �� ������." << endl;
	system("pause");
}
