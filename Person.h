#pragma once
#include <string>
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
		const int FULL_NAME_MIN_LENGTH = 6;
		const int FULL_NAME_MAX_LENGTH = 100;
		const char FULL_NAME_ALLOWED_CHARS[] = "יצףךוםדרשחץתפûגאןנמכהז‎ÿקסלטעüב‏ÉÖÓÊÅÍÃØÙÇÕÚÔÛÂÀÏÐÎËÄÆÝ‗×ÑÌÈÒÜÁÞ -";
	}
};
