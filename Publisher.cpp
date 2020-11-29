#include "pch.h"
#include "Publisher.h"

Utils::FileBindedVector<Publisher> Publisher::binder("publishers.txt");
int Publisher::lastId = -1;

namespace Constraints
{
	namespace Publisher
	{
		const int NAME_MIN_LENGTH = 4;
		const int NAME_MAX_LENGTH = 64;
		const string NAME_ALLOWED_CHARS = Constraints::CharacterSets::EXTENDED;
	}
}

Publisher* Publisher::loadRecord(ifstream & fin)
{
	string id;
	string name;
	getline(fin, id);
	getline(fin, name);
	if (fin.eof() || fin.fail()) return nullptr;
	return new Publisher(name, stoi(id));
}

void Publisher::saveRecord(ofstream & fout)
{
	fout << id << endl << name << endl;
}
