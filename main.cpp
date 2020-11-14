#include "pch.h"
#include <iostream>
#include "MenuDefs.h"
#include "Console.h"
#include <thread>
#include <mutex>
#include "User.h"
#include "Publisher.h"
using namespace std;
//mutex g_mutex;

int main()
{
	// Подготавливаем консоль
	//Utils::setupResolution();
	Utils::setupEncoding();

	// Инициализиуем меню и их взаимосвязи
	menuInitAll();

	// Загружаем данные
	User::getBinder().loadRecords();
	User::getBinderUnconfirmed().loadRecords();
	Publisher::getBinder().loadRecords();
	if (Publisher::getBinder().getRecords().size())
	{
		Publisher::getLastId() = Publisher::getBinder().getRecords().rend().operator*()->getId();
	}
	else
	{
		Publisher::getLastId() = 0;
	}

	// Запускаем циклы работы с меню в отдельных потоках
	thread t1(menuControlLoop);
	thread t2(menuPrintLoop);
	t1.join();
	t2.join();
	cout << "Выход из программы..." << endl;
}
