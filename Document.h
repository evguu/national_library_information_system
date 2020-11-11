#pragma once
#include "Publisher.h"
#include <string>
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
public:
	Document(Type type, Language language, Publisher* publisher, string title, int pageCount) :type(type), language(language), publisher(publisher), title(title), pageCount(pageCount) {};
	~Document() {};
	auto& getType() { return type; };
	auto& getLanguage() { return language; };
	auto& getPublisher() { return publisher; };
	auto& getTitle() { return title; };
	auto& getPageCount() { return pageCount; };
};

