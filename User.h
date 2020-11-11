#pragma once
#include <string>
#include "Encrypt.h"
#include "Person.h"
using namespace std;

class User :
	public Person
{
private:
	string login; // UID
	string encryptedPassword;
	bool isAdmin;
public:
	User(string fullName, string login, string password, bool isAdmin) : Person(fullName), login(login), encryptedPassword(Utils::encrypt(password)), isAdmin(isAdmin) {};
	~User() {};
	const auto& getLogin() { return login; };
	auto& getEncryptedPassword() { return encryptedPassword; };
	auto& getIsAdmin() { return isAdmin; };
};
