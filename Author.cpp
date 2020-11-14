#include "pch.h"
#include "Author.h"

Utils::FileBindedVector<Author> Author::binder("authors.txt");
int Author::lastId = -1;

Author * Author::loadRecord(ifstream & fin)
{
	string fullName;
	string id;
	getline(fin, fullName);
	getline(fin, id);
	if (fin.eof() || fin.fail()) return nullptr;
	return new Author(fullName, stoi(id));
}

void Author::saveRecord(ofstream & fout)
{
	fout << getFullName() << endl << id << endl;
}
