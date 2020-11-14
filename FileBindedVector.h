#pragma once
#include <vector>
#include <string>
#include <fstream>

#define IDBI(x) x::getBinder().loadRecords(); if (x::getBinder().getRecords().size()) { x::getLastId() = x::getBinder().getRecords().rend().operator*()->getId(); } else { x::getLastId() = 0; }

using namespace std;

namespace Utils
{
	template <class T>
	class FileBindedVector
	{
		// Класс T должен иметь два метода:
		// static T* loadRecord(ifstream& fin)
		// void saveRecord(ofstream& fout)
	private:
		string filename;
		vector<T*> records;
	public:
		FileBindedVector(string filename) : filename(filename) {};
		~FileBindedVector() {};
		auto& getRecords() { return records; };
		void loadRecords() 
		{
			ifstream fin;
			// Защита от утечки памяти
			for (auto it : records)
			{
				delete it;
			}
			records.clear();
			fin.open(filename, ios::in);
			while (!fin.eof() && !fin.fail())
			{
				T* record = T::loadRecord(fin);
				if (record)
				{
					records.push_back(record);
				}
				else
				{
					break;
				}
			}
			fin.close();
		};
		void saveRecords()
		{
			ofstream fout;
			fout.open(filename, ios::out);
			for (auto it : records)
			{
				it->saveRecord(fout);
			}
			fout.close();
		};
	};
}
