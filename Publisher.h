#pragma once
#include <string>
using namespace std;

class Publisher
{
private:
	string name;
public:
	Publisher(string name) : name(name) {};
	~Publisher() {};
	auto& getName() { return name; };
};
