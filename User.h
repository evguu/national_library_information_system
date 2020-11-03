#pragma once
#include <string>
#include "Encrypt.h"
using namespace std;

namespace MainTypes
{
	class User;

	class User
	{
	private:
		static User* active;
		string login;
		string encryptedPassword;
		string firstName;
		string lastName;
		bool isAdmin;
	public:
		// Создание и разрушение
		User(string login, string password, bool isAdmin, string firstName, string lastName) :
			login(login), encryptedPassword(Utils::encrypt(password)), isAdmin(isAdmin), firstName(firstName), lastName(lastName) {};
		~User();

		// Интерфейс
		static void setActive(User* user) { active = user; };
		static User* getActive() { return active; };

		void setIsAdmin(bool isAdmin) { this->isAdmin = isAdmin; };
		void setFirstName(string firstName) { this->firstName = firstName; };
		void setLastName(string firstName) { this->lastName = lastName; };
		void setEncryptedPassword(string password) { encryptedPassword = Utils::encrypt(password); };

		bool getIsAdmin() { return isAdmin; }
		string getFirstName() { return firstName; };
		string getLastName() { return lastName; };
		string getEncryptedPassword(string password) { return encryptedPassword; };
		string getLogin() { return login; };

		static void login_(string login, string password);
		static void register_(string login, string password, string repeatPassword);
	};
}
