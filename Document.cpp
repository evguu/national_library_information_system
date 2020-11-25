#include "pch.h"
#include "Document.h"

Utils::FileBindedVector<Document> Document::binder("documents.txt");
int Document::lastId = -1;
const vector<string> Document::types = {
	"Книга",
	"Автореферат диссертации", 
	"Статья",
	"Нотный документ",
	"Диссертация",
	"Другое" 
};
const vector<string> Document::languages = {
	"Русский",
	"Английский",
	"Белорусский",
	"Украинский",
	"Польский",
	"Немецкий",
	"Французский",
	"Чешский",
	"Латинский",
	"Болгарский",
	"Другое"
};

namespace Constraints
{
	namespace Document
	{
		const int TITLE_MIN_LENGTH = 1;
	    const int TITLE_MAX_LENGTH = 128;
		const string TITLE_ALLOWED_CHARS = Constraints::CharacterSets::EXTENDED;
	}
}

Document * Document::loadRecord(ifstream & fin)
{
	string type;
	string language;
	string publisher;
	string title;
	string pageCount;
	string id;
	getline(fin, type);
	getline(fin, language);
	getline(fin, publisher);
	getline(fin, title);
	getline(fin, pageCount);
	getline(fin, id);
	if (fin.eof() || fin.fail()) return nullptr;
	for (auto it : Publisher::getBinder().getRecords())
	{
		if (it->getId() == stoi(publisher))
		{
			return new Document(static_cast<Type>(stoi(type)), static_cast<Language>(stoi(language)), it, title, stoi(pageCount), stoi(id));
		}
	}
	return (Document *)Utils::FBV_CORRUPTED_DATA;
}

void Document::saveRecord(ofstream & fout)
{
	fout << static_cast<int>(type) << endl << static_cast<int>(language) << endl << publisher->getId() << endl << title << endl << pageCount << endl << id << endl;
}
