#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <time.h>
using namespace std;

void addLog(string log)
{
	tm ltm;
	time_t tt = time(0);
	localtime_s(&ltm, &tt);
	std::stringstream date;
	date << ltm.tm_mday << "/" << ((1 + ltm.tm_mon >= 10) ? ("") : ("0")) << 1 + ltm.tm_mon << "/"
		<< 1900 + ltm.tm_year << " " << ((1 + ltm.tm_hour >= 10) ? ("") : ("0")) << 1 + ltm.tm_hour
		<< ":" << ((1 + ltm.tm_min >= 10) ? ("") : ("0")) << 1 + ltm.tm_min
		<< ":" << ((1 + ltm.tm_sec >= 10) ? ("") : ("0")) << 1 + ltm.tm_sec;
	ofstream fout;
	fout.open("logs.txt", ios::app);
	fout << "[ " << date.str() << "]: " << log << endl;
	fout.close();
}

void printLogs()
{
	ifstream f("logs.txt");
	string str;
	if (f) {
		ostringstream ss;
		ss << f.rdbuf();
		str = ss.str();
	}
	cout << str;
}

void clearLogs()
{
	ofstream fout;
	fout.open("logs.txt", ios::out);
	fout.close();
}