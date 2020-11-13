#pragma once
#include "Person.h"
class Author :
	public Person
{
public:
	Author(string fullName) : Person(fullName) {};
	~Author() {};
};

