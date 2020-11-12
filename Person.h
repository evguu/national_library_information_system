#pragma once
#include <string>
#include "CharacterSets.h"
using namespace std;

class Person
{
private:
	string fullName;
public:
	Person(string fullName) : fullName(fullName) {};
	~Person() {};

	auto& getFullName() { return fullName; }
};

namespace Constraints
{
	namespace Person
	{
		extern const int FULL_NAME_MIN_LENGTH;
		extern const int FULL_NAME_MAX_LENGTH;
		extern const string FULL_NAME_ALLOWED_CHARS;
	}
};
