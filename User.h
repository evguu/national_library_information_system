#pragma once
#include <string>
#include "Encrypt.h"
#include "Person.h"
#include <vector>
using namespace std;

class User;

class User :
	public Person
{
private:
	string login; // UID
	string encryptedPassword;
	bool isAdmin;
	static User* activeUser;
	vector<User *> recordedInstances;
public:
	User(string fullName, string login, string password, bool isAdmin) : Person(fullName), login(login), encryptedPassword(Utils::encrypt(password)), isAdmin(isAdmin) {};
	~User() {};
	const auto& getLogin() { return login; };
	auto& getEncryptedPassword() { return encryptedPassword; };
	auto& getIsAdmin() { return isAdmin; };
	static auto& getActiveUser() { return activeUser; };
	static void registerUser(string login, string password, string repeatPassword);
	static void loginUser(string login, string password);
};
