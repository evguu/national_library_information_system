#include "pch.h"
#include "DocumentAuthorBind.h"

Utils::FileBindedVector<DocumentAuthorBind> DocumentAuthorBind::binder("document_author_binds.txt");

DocumentAuthorBind * DocumentAuthorBind::loadRecord(ifstream & fin)
{
	string document;
	string author;
	getline(fin, document);
	getline(fin, author);
	if (fin.eof() || fin.fail()) return nullptr;
	for (auto document_it : Document::getBinder().getRecords())
	{
		if (document_it->getId() == stoi(document))
		{
			for (auto author_it : Author::getBinder().getRecords())
			{
				if (author_it->getId() == stoi(author))
				{
					return new DocumentAuthorBind(document_it, author_it);
				}
			}
		}
	}
	return (DocumentAuthorBind*)Utils::FBV_CORRUPTED_DATA;
}

void DocumentAuthorBind::saveRecord(ofstream & fout)
{
	fout << document->getId() << endl << author->getId() << endl;
}
