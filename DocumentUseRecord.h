#pragma once
#include "Document.h"
#include "Reader.h"
#include "FileBindedVector.h"
#include "CharacterSets.h"
#include <sstream>
#include <time.h>
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

	static void searchByDocumentId(int id, vector<DocumentUseRecord *>& results)
	{
		results.clear();
		for (auto it : binder.getRecords())
		{
			if (it->getDocument()->getId() == id)
			{
				results.push_back(it);
			}
		}
	}

	static void searchByReaderId(int id, vector<DocumentUseRecord *>& results)
	{
		results.clear();
		for (auto it : binder.getRecords())
		{
			if (it->getReader()->getId() == id)
			{
				results.push_back(it);
			}
		}
	}

	string strGivenAt()
	{
		tm ltm;
		localtime_s(&ltm, &givenAt);
		std::stringstream date;
		date << ltm.tm_mday << "/" << ((1 + ltm.tm_mon >= 10)?(""):("0")) << 1 + ltm.tm_mon<< "/"
			<< 1900 + ltm.tm_year << " " << ((1 + ltm.tm_hour >= 10) ? ("") : ("0")) << 1 + ltm.tm_hour
			<< ":" << ((1 + ltm.tm_min >= 10) ? ("") : ("0")) << 1 + ltm.tm_min
			<< ":" << ((1 + ltm.tm_sec >= 10) ? ("") : ("0")) << 1 + ltm.tm_sec;
		return date.str();
	}
	string str(bool skipDocument = false) {
		string result;
		if (!skipDocument)
		{
			result += "Документ" + document->str() + " ";
		}
		result += "читателю " + reader->str() + " выдан " + strGivenAt() + " на " + to_string(givenFor) + " часов.";
		return result;
	};
};

