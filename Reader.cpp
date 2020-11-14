#include "pch.h"
#include "Reader.h"

Utils::FileBindedVector<Reader> Reader::binder("readers.txt");

Reader * Reader::loadRecord(ifstream & fin)
{
	string fullName;
	string phoneNumber;
	string address;
	string passportId;
	getline(fin, fullName);
	getline(fin, phoneNumber);
	getline(fin, address);
	getline(fin, passportId);
	if (fin.eof() || fin.fail()) return nullptr;
	return new Reader(fullName, phoneNumber, address, passportId);
}

void Reader::saveRecord(ofstream & fout)
{
	fout << getFullName() << endl << phoneNumber << endl << address << endl << passportId << endl;
}
