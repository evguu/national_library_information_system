#include "pch.h"
#include "Reader.h"

Utils::FileBindedVector<Reader> Reader::binder("readers.txt");
int Reader::lastId = -1;

Reader * Reader::loadRecord(ifstream & fin)
{
	string fullName;
	string phoneNumber;
	string address;
	string passportId;
	string id;
	getline(fin, fullName);
	getline(fin, phoneNumber);
	getline(fin, address);
	getline(fin, passportId);
	getline(fin, id);
	if (fin.eof() || fin.fail()) return nullptr;
	return new Reader(fullName, phoneNumber, address, passportId, stoi(id));
}

void Reader::saveRecord(ofstream & fout)
{
	fout << getFullName() << endl << phoneNumber << endl << address << endl << passportId << endl << id << endl;
}
