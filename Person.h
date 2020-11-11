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

