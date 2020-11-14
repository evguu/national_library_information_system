#pragma once
#include "Document.h"
#include "Reader.h"
#include "FileBindedVector.h"
#include "CharacterSets.h"
using namespace std;

class DocumentUseRecord
{
private:
	Document* document;
	Reader* reader;
	time_t givenAt;
	int givenFor;
	static Utils::FileBindedVector<DocumentUseRecord> binder;
public:
	DocumentUseRecord(Document* document, Reader* reader, time_t givenAt, int givenFor) : document(document), reader(reader), givenAt(givenAt), givenFor(givenFor) {};
	~DocumentUseRecord() {};
	auto& getDocument() { return document; };
	auto& getReader() { return reader; };
	auto& getGivenAt() { return givenAt; };
	auto& getGivenFor() { return givenFor; };

	static auto& getBinder() { return binder; };
	static DocumentUseRecord* loadRecord(ifstream& fin);
	void saveRecord(ofstream& fout);
};

