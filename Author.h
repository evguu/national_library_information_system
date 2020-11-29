#pragma once
#include "Person.h"
#include <string>
#include "FileBindedVector.h"
#include "CharacterSets.h"
using namespace std;

class Author :
	public Person
{
private:
	int id;
	static int lastId;
	static Utils::FileBindedVector<Author> binder;
public:
	Author(string fullName, int id = ++lastId) : Person(fullName), id(id) {};
	~Author() {};
	static auto& getLastId() { return lastId; };
	auto& getId() { return id; };

	static auto& getBinder() { return binder; };
	static Author* loadRecord(ifstream& fin);
	void saveRecord(ofstream& fout);

	string str() { return getFullName(); };
};

