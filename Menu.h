#pragma once
#include <stack>
#include <vector>
#include <mutex>
#include "MenuElements.h"

using namespace std;

class Menu;

// Класс для организации пользовательского интерфейса в виде меню
class Menu
{
private:
	// Стек меню
	static stack<Menu *> menuStack;
	// Используется для завершения потоков меню
	static bool isLoopRunning;
	// Используется для контроля обновлений экрана
	static bool hasMenuChanged;
	// Используется во избежание конфликта потоков
	static mutex g_lock;
	// Используется для контроля числа выводимых на экран элементов
	static const int viewField;
	// Хранит элементы меню
	vector<MenuElement *> elements;
	// Хранит индекс активного элемента в векторе элементов
	int chosenElementIndex;
	// Контролирующий поток. Отвечает за обработку ввода
	static void controlLoop();
	// Печатащий поток. Отвечает за обработку вывода
	static void printLoop();
public:
	// По умолчанию индекс выбранного элемента -1, что приведет к падению программы при некорректной инициализации меню
	Menu() : chosenElementIndex(-1) {};
	// Так как элементы меню создаются динамически, необходимо освобождать за собой память
	~Menu()
	{
		for (auto it:elements)
		{ 
			delete it;
		}
	};
	// Строковое представление меню
	string str() const;
	// Обработчик нажатий
	bool recvCommand(int keyEvent);
	// Добавляет элемент в меню. Для удобства MenuElements.h определяет макросы категории NME
	void addElement(MenuElement* ref);
	// Добавляет меню на стек меню
	void addToStack();
	// Возвращает по ссылке вектор элементов
	auto& getElements() { return elements; }
	// Вычисляет индекс первого элемента, который можно выбрать и выбирает его
	void initChosenElementIndex();
	// Возвращает по значению индекс выбранного элемента
	int getChosenElementIndex() { return chosenElementIndex; };
	// Сбрасывает элементы и позицию курсора
	void reset();
	// Возвращает верхнее меню со стека
	static Menu* getActive() { return menuStack.top(); };
	// Снимает со стека заданное число меню
	static void multiPopMenuStack(int popCount = 1);
	// Берет на себя взаимодействие с пользователем
	static void run()
	{
		thread t1(controlLoop);
		thread t2(printLoop);
		t1.join();
		t2.join();
	}
	// Завершает потоки меню
	static void finish() { isLoopRunning = false; };
	// Возвращает по значению мьютекс потоков меню
	static auto& getMutex() { return g_lock; };
	// Оператор вывода меню в поток
	friend ostream &operator << (ostream &, Menu &);
};
