#pragma once
#include <string>
#include "Encrypt.h"
#include "Person.h"
#include <vector>
#include "FileBindedVector.h"
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
	static Utils::FileBindedVector<User> binder;
public:
	User(string fullName, string login, string password, bool isAdmin) : Person(fullName), login(login), encryptedPassword(Utils::encrypt(password)), isAdmin(isAdmin) {};
	~User() {};

	const auto& getLogin() { return login; };
	auto& getEncryptedPassword() { return encryptedPassword; };
	auto& getIsAdmin() { return isAdmin; };
	static auto& getActiveUser() { return activeUser; };

	static auto& getBinder() { return binder; };
	static User* loadRecord(ifstream& fin) {};
	void saveRecord(ofstream& fout) {};

	static void registerUser(string login, string password, string repeatPassword);
	static void loginUser(string login, string password);
};
