#include "pch.h"
#include "User.h"
#include "Encrypt.h"
using namespace std;

namespace MainTypes
{
	User* User::active = nullptr;

	User::~User()
	{
	}

	void User::login_(string login, string password)
	{
	}

	void User::register_(string login, string password, string repeatPassword)
	{
	}
}
