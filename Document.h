#pragma once
#include "Publisher.h"
#include <string>
#include "FileBindedVector.h"
#include "CharacterSets.h"
using namespace std;

class Document
{
public:
	enum class Type
	{
		BOOK,
		MAGAZINE,
		OTHER
	};
	enum class Language
	{
		RUSSIAN,
		ENGLISH,
		POLISH,
		UKRAINIAN,
		BELARUSIAN,
		OTHER
	};
private:
	Type type;
	Language language;
	Publisher* publisher;
	string title;
	int pageCount;
	int id;
	static int lastId;
	static Utils::FileBindedVector<Document> binder;
public:
	Document(Type type, Language language, Publisher* publisher, string title, int pageCount, int id = ++lastId) :type(type), language(language), publisher(publisher), title(title), pageCount(pageCount), id(id) {};
	~Document() {};
	auto& getType() { return type; };
	auto& getLanguage() { return language; };
	auto& getPublisher() { return publisher; };
	auto& getTitle() { return title; };
	auto& getPageCount() { return pageCount; };
	static auto& getLastId() { return lastId; };
	auto& getId() { return id; };

	static auto& getBinder() { return binder; };
	static Document* loadRecord(ifstream& fin);
	void saveRecord(ofstream& fout);
};

namespace Constraints
{
	namespace Document
	{
		extern const int TITLE_MIN_LENGTH;
		extern const int TITLE_MAX_LENGTH;
		extern const string TITLE_ALLOWED_CHARS;
	}
}