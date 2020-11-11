#pragma once
#include <vector>
#include <string>
#include <fstream>
using namespace std;

namespace Utils
{
	template <typename T>
	class FileBindedVector;
	class IFileBindable;

	template <typename T>
	class FileBindedVector
	{
		// Класс T должен иметь два метода:
		// static T* loadRecord(ifstream fin)
		// void saveRecord(ofstream fout)
	private:
		string filename;
		vector<T*> records;
	public:
		FileBindedVector(string filename) : filename(filename) {};
		auto& getRecords() { return records; };
		void loadRecords();
		void saveRecords();
	};

}
