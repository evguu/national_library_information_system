#include "pch.h"
#include "User.h"
#include "Encrypt.h"
using namespace std;

User* User::activeUser = nullptr;
Utils::FileBindedVector<User> User::binder("users.txt");

void User::registerUser(string login, string password, string repeatPassword)
{
}

void User::loginUser(string login, string password)
{
}
