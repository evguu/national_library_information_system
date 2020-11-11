#pragma once
#include "Person.h"
#include <string>
using namespace std;

class Reader :
	public Person
{
private:
	string phoneNumber;
	string address;
	string passportId;
public:
	Reader(string fullName, string phoneNumber, string address, string passportId) : Person(fullName), phoneNumber(phoneNumber), address(address), passportId(passportId) {};
	~Reader() {};
	auto& getPhoneNumber() { return phoneNumber; };
	auto& getAddress() { return address; };
	auto& getPassportId() { return passportId; };
};

