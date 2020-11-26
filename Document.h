#pragma once
#include "Publisher.h"
#include <string>
#include "FileBindedVector.h"
#include "CharacterSets.h"
using namespace std;

class Document
{
public:
	// ”бедительна€ просьба не трогать этот подкласс без попутного изменени€ соответствующего вектора строк!
	enum class Type
	{
		BOOK,
		AUTOREFERAT_DISSERTATION,
		ARTICLE,
		NOTE_DOCUMENT,
		DISSERTATION,
		OTHER
	};

	// ”бедительна€ просьба не трогать этот подкласс без попутного изменени€ соответствующего вектора строк!
	enum class Language
	{
		RUSSIAN,
		ENGLISH,
		BELARUSIAN,
		UKRAINIAN,
		POLISH,
		GERMAN,
		FRENCH,
		CHEZH,
		LATIN,
		BULGARIAN,
		OTHER
	};

	static const vector<string> types;
	static const vector<string> languages;
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

	string str() { return to_string(id) + ". " + title + " [ »здатель: " + publisher->str() + "]"; };
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