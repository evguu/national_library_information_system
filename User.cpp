#include "pch.h"
#include "User.h"
#include "Encrypt.h"
#include "iostream"
using namespace std;

User* User::activeUser = nullptr;
Utils::FileBindedVector<User> User::binder("users.txt");
Utils::FileBindedVector<User> User::binderUnconfirmed("users_unconfirmed.txt");

User * User::loadRecord(ifstream & fin)
{
	string fullName;
	string login;
	string encryptedPassword;
	bool isAdmin;
	fin >> fullName >> login >> encryptedPassword >> isAdmin;
	if (fin.eof()) return nullptr;
	return new User(fullName, login, encryptedPassword, isAdmin);
}

void User::saveRecord(ofstream & fout)
{
	fout << getFullName() << endl << login << endl << encryptedPassword << endl << isAdmin << endl;
}

void User::registerUser(string fullName, string login, string password, string repeatPassword)
{
	if (password != repeatPassword)
	{
		cout << "������ �� ���������." << endl;
	}
	else if (!fullName.length() || !login.length() || !password.length() || !repeatPassword.length())
	{
		cout << "��� ���� ������ ���� ���������." << endl;
	}
	else if (fullName.length() < Constraints::Person::FULL_NAME_MIN_LENGTH)
	{
		cout << "��� �� ����� ���� ������ " << Constraints::Person::FULL_NAME_MIN_LENGTH << " ��������." << endl;
	}
	else if (login.length() < Constraints::User::LOGIN_MIN_LENGTH)
	{
		cout << "����� �� ����� ���� ������ " << Constraints::User::LOGIN_MIN_LENGTH << " ��������." << endl;
	}
	else if (password.length() < Constraints::User::PASSWORD_MIN_LENGTH)
	{
		cout << "������ �� ����� ���� ������ " << Constraints::User::PASSWORD_MIN_LENGTH << " ��������." << endl;
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
				break;
			}
		}
		if (!isLoginAlreadyTaken)
		{
			cout << "������� ������� ���������������. \n�� ������� ����� ����� ������������� �������� ���������������." << endl;
			binderUnconfirmed.getRecords().push_back(new User(fullName, login, password, false));
			binderUnconfirmed.saveRecords();
		}
	}
	system("pause");
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
}
