#pragma once
#include "Document.h"
#include "Reader.h"

class DocumentUseRecord
{
private:
	Document* document;
	Reader* reader;
	time_t givenAt;
	int givenFor;
public:
	DocumentUseRecord(Document* document, Reader* reader, time_t givenAt, int givenFor) : document(document), reader(reader), givenAt(givenAt), givenFor(givenFor) {};
	~DocumentUseRecord() {};
	auto& getDocument() { return document; };
	auto& getReader() { return reader; };
	auto& getGivenAt() { return givenAt; };
	auto& getGivenFor() { return givenFor; };
};

