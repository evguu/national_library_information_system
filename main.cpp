﻿#include "pch.h"
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
	Publisher::getLastId() = Publisher::getBinder().getRecords().end().operator*()->getId();

	// Запускаем циклы работы с меню в отдельных потоках
	thread t1(menuControlLoop);
	thread t2(menuPrintLoop);
	t1.join();
	t2.join();
	cout << "Выход из программы..." << endl;
}
