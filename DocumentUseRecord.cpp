#include "pch.h"
#include "DocumentUseRecord.h"

Utils::FileBindedVector<DocumentUseRecord> DocumentUseRecord::binder("document_use_records.txt");

DocumentUseRecord * DocumentUseRecord::loadRecord(ifstream & fin)
{
	string document;
	string reader;
	string givenAt;
	string givenFor;
	getline(fin, document);
	getline(fin, reader);
	getline(fin, givenAt);
	getline(fin, givenFor);
	if (fin.eof() || fin.fail()) return nullptr;
	for (auto document_it : Document::getBinder().getRecords())
	{
		if (document_it->getId() == stoi(document))
		{
			for (auto reader_it : Reader::getBinder().getRecords())
			{
				if (reader_it->getId() == stoi(reader))
				{
					return new DocumentUseRecord(document_it, reader_it, stoi(givenAt), stoi(givenFor));
				}
			}
		}
	}
	return (DocumentUseRecord*)Utils::FBV_CORRUPTED_DATA;
}

void DocumentUseRecord::saveRecord(ofstream & fout)
{
	fout << document->getId() << endl << reader->getId() << endl << givenAt << endl << givenFor << endl;
}
