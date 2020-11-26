#pragma once
#include "Person.h"
#include <string>
#include "FileBindedVector.h"
#include "CharacterSets.h"
using namespace std;

class Reader :
	public Person
{
private:
	string phoneNumber;
	string address;
	string passportId;
	int id;
	static int lastId;
	static Utils::FileBindedVector<Reader> binder;
public:
	Reader(string fullName, string phoneNumber, string address, string passportId, int id = ++lastId) : Person(fullName), phoneNumber(phoneNumber), address(address), passportId(passportId), id(id) {};
	~Reader() {};
	auto& getPhoneNumber() { return phoneNumber; };
	auto& getAddress() { return address; };
	auto& getPassportId() { return passportId; };
	static auto& getLastId() { return lastId; };
	auto& getId() { return id; };

	static auto& getBinder() { return binder; };
	static Reader* loadRecord(ifstream& fin);
	void saveRecord(ofstream& fout);

	string str() { return id + ". " + getFullName(); };
};

namespace Constraints
{
	namespace Reader
	{
		extern const int PHONE_NUMBER_MIN_LENGTH;
		extern const int PHONE_NUMBER_MAX_LENGTH;
		extern const string PHONE_NUMBER_ALLOWED_CHARS;
		extern const int ADDRESS_MIN_LENGTH;
		extern const int ADDRESS_MAX_LENGTH;
		extern const string ADDRESS_ALLOWED_CHARS;
		extern const int PASSPORT_ID_MIN_LENGTH;
		extern const int PASSPORT_ID_MAX_LENGTH;
		extern const string PASSPORT_ID_ALLOWED_CHARS;
	}
}