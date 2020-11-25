#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

// Используется для корректной загрузки объектов класса, использующего FileBindedVector.
// Стоит учитывать, что макрос не сработает, если целевой FileBindedVector недоступен по функции getBinder().
#define IDBI(x) x::getBinder().loadRecords(); if (x::getBinder().getRecords().size()) { x::getLastId() = x::getBinder().getRecords().back()->getId(); } else { x::getLastId() = 0; }

using namespace std;

namespace Utils
{
	extern const void* FBV_CORRUPTED_DATA;

	template <class T>
	class FileBindedVector
	{
		// Класс T должен иметь два метода:
		// 1) static T* loadRecord(ifstream& fin)
		// 2) void saveRecord(ofstream& fout)

		// Класс FileBindedVector используется для упрощения связи классов, предусматривающих хранение объектов в централизированном векторе, с файлами.
	private:
		string filename;
		vector<T*> records;
	public:
		FileBindedVector(string filename) : filename(filename) {};
		~FileBindedVector() 
		{
			for (auto it : records)
			{
				if (it) delete it;
			}
			records.clear();
		};
		auto& getRecords() { return records; };
		void loadRecords() 
		{
			ifstream fin;
			for (auto it : records)
			{
				if (it) delete it;
			}
			records.clear();
			fin.open(filename, ios::in);
			while (!fin.eof() && !fin.fail())
			{
				T* record = T::loadRecord(fin);
				if((void *)record == FBV_CORRUPTED_DATA)
				{
					cout << "Обнаружено повреждение данных. Пожалуйста, сообщите администратору. В повреждении подозревается файл: " << filename << ", а также его зависимые файлы." << endl;
					system("pause");
					break;
				}
				else if (record)
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
