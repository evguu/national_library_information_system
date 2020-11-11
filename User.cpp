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
		cout << "Пароли не совпадают." << endl;
	}
	else if (!fullName.length() || !login.length() || !password.length() || !repeatPassword.length())
	{
		cout << "Все поля должны быть заполнены." << endl;
	}
	else if (fullName.length() < Constraints::Person::FULL_NAME_MIN_LENGTH)
	{
		cout << "ФИО не может быть короче " << Constraints::Person::FULL_NAME_MIN_LENGTH << " символов." << endl;
	}
	else if (login.length() < Constraints::User::LOGIN_MIN_LENGTH)
	{
		cout << "Логин не может быть короче " << Constraints::User::LOGIN_MIN_LENGTH << " символов." << endl;
	}
	else if (password.length() < Constraints::User::PASSWORD_MIN_LENGTH)
	{
		cout << "Пароль не может быть короче " << Constraints::User::PASSWORD_MIN_LENGTH << " символов." << endl;
	}
	else
	{
		bool isLoginAlreadyTaken = false;
		for (auto it : binder.getRecords())
		{
			if (login == it->getLogin())
			{
				cout << "Логин уже занят." << endl;
				isLoginAlreadyTaken = true;
				break;
			}
		}
		for (auto it : binderUnconfirmed.getRecords())
		{
			if (isLoginAlreadyTaken) break;
			if (login == it->getLogin())
			{
				cout << "Логин уже занят неподтвержденным пользователем." << endl;
				isLoginAlreadyTaken = true;
				break;
			}
		}
		if (!isLoginAlreadyTaken)
		{
			cout << "Аккаунт успешно зарегистрирован. \nВы сможете войти после подтверждения аккаунта администратором." << endl;
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
				cout << "Добро пожаловать, " << it->getFullName() << "!" << endl;
			}
			else
			{
				cout << "Пароль неверный." << endl;
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
				cout << it->getFullName() << ", ваш аккаунт требует подтверждения администратором." << endl;
			}
			else
			{
				cout << "Пароль неверный." << endl;
			}
			system("pause");
			return;
		}
	}
}
