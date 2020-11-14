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
	static Utils::FileBindedVector<Reader> binder;
public:
	Reader(string fullName, string phoneNumber, string address, string passportId) : Person(fullName), phoneNumber(phoneNumber), address(address), passportId(passportId) {};
	~Reader() {};
	auto& getPhoneNumber() { return phoneNumber; };
	auto& getAddress() { return address; };
	auto& getPassportId() { return passportId; };

	static auto& getBinder() { return binder; };
	static Reader* loadRecord(ifstream& fin);
	void saveRecord(ofstream& fout);
};

