#pragma once
#include <string>
#include "FileBindedVector.h"
#include "CharacterSets.h"
using namespace std;

class Publisher
{
private:
	string name;
	int id;
	static int lastId;
	static Utils::FileBindedVector<Publisher> binder;
public:
	Publisher(string name, int id = ++lastId) : name(name), id(id) {};
	~Publisher() {};
	auto& getName() { return name; };
	static auto& getLastId() { return lastId; };
	auto& getId() { return id; };

	static auto& getBinder() { return binder; };
	static Publisher* loadRecord(ifstream& fin);
	void saveRecord(ofstream& fout);
};

namespace Constraints
{
	namespace Publisher
	{
		extern const int NAME_MIN_LENGTH;
		extern const int NAME_MAX_LENGTH;
		extern const string NAME_ALLOWED_CHARS;
	}
}