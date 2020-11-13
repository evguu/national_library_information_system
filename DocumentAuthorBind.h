#pragma once
#include "Document.h"
#include "Author.h"
class DocumentAuthorBind
{
private:
	Document* document;
	Author* author;
public:
	DocumentAuthorBind(Document* document, Author* author) : document(document), author(author) {};
	~DocumentAuthorBind() {};
	auto& getDocument() { return document; };
	auto& getAuthor() { return author; };
};

