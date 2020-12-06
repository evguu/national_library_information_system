#pragma once

#define ELK Menu::getMutex().lock();system("MODE CON: COLS=128 LINES=200");system("cls");
#define EULK system("pause");system("MODE CON: COLS=128 LINES=40");system("cls");Menu::getMutex().unlock();
