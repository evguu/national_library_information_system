#pragma once
#include <vector>
#include <string>
#include <fstream>

// Используется для корректной загрузки объектов класса, использующего FileBindedVector.
// Стоит учитывать, что данный макрос не сработает, если целевой FileBindedVector недоступен по функции getBinder().
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

		// Класс FileBindedVector используется для упрощения связи классов, предусматривающих хранение объектов в централизированном векторе, с файлами.
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
