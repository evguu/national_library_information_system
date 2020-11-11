#include "pch.h"
#include "FileBindedVector.h"

namespace Utils
{
	template<typename T>
	void FileBindedVector<T>::loadRecords()
	{
		ifstream fin;
		records.clear();
		fin.open(filename, ios::in);
		while (!fin.eof())
		{
			auto record = T::loadRecord();
			if (record)
			{
				records.push_back(record);
			}
		}
		fin.close();
	}

	template<typename T>
	void FileBindedVector<T>::saveRecords()
	{
		ofstream fout;
		fout.open(filename, ios::out);
		for (auto it : records)
		{
			it.saveRecord(fout);
		}
		fout.close();
	}
}