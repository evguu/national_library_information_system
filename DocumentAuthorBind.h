#pragma once
#include "Document.h"
#include "Author.h"
#include "FileBindedVector.h"
#include "CharacterSets.h"
#include <algorithm>
using namespace std;

class DocumentAuthorBind
{
private:
	Document* document;
	Author* author;
	static Utils::FileBindedVector<DocumentAuthorBind> binder;
public:
	DocumentAuthorBind(Document* document, Author* author) : document(document), author(author) {};
	~DocumentAuthorBind() {};
	auto& getDocument() { return document; };
	auto& getAuthor() { return author; };

	static auto& getBinder() { return binder; };
	static DocumentAuthorBind* loadRecord(ifstream& fin);
	void saveRecord(ofstream& fout);

	string str() { return "Документ " + document->str() + " имеет автора " + author->str(); };

	static void searchByDocumentId(int id, vector<DocumentAuthorBind *>& results)
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

	static void unsearchByRelatedBinds(vector<Author *>& results, const vector<DocumentAuthorBind *>& relatedBinds)
	{
		results.clear();
		vector<Author *>takenVector;
		for (auto it : relatedBinds)
		{
			takenVector.push_back(it->getAuthor());
		}
		for (auto it : Author::getBinder().getRecords())
		{
			if (find(takenVector.begin(), takenVector.end(), it) == takenVector.end())
			{
				results.push_back(it);
			}
		}
	}
};

