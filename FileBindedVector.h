#pragma once
#include <vector>
#include <string>
#include <fstream>
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
			records.clear();
			fin.open(filename, ios::in);
			while (!fin.eof())
			{
				T* record = T::loadRecord();
				if (record)
				{
					records.push_back(record);
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
