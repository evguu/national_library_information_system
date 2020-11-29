#include "pch.h"
#include "Reader.h"

Utils::FileBindedVector<Reader> Reader::binder("readers.txt");
int Reader::lastId = -1;

namespace Constraints
{
	namespace Reader
	{
		const int PHONE_NUMBER_MIN_LENGTH = 6;
		const int PHONE_NUMBER_MAX_LENGTH = 14;
		const string PHONE_NUMBER_ALLOWED_CHARS = "+" + Constraints::CharacterSets::NUMBERS;
		const int ADDRESS_MIN_LENGTH = 10;
		const int ADDRESS_MAX_LENGTH = 100;
		const string ADDRESS_ALLOWED_CHARS = Constraints::CharacterSets::EXTENDED;
		const int PASSPORT_ID_MIN_LENGTH = 14;
		const int PASSPORT_ID_MAX_LENGTH = 14;
		const string PASSPORT_ID_ALLOWED_CHARS = Constraints::CharacterSets::NUMBERS + Constraints::CharacterSets::ENGLISH_UPPER;
	}
}

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
