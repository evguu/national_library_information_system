#pragma once

// Макрос для создания поля ввода с ограничениями
#define CH_NME_EDIT_FIELD(z, x, y) NME_EDIT_FIELD(z, false, Constraints::x::##y##_ALLOWED_CHARS, Constraints::x::##y##_MIN_LENGTH, Constraints::x::##y##_MAX_LENGTH);

// Макрос для создания поля ввода с ограничениями и скрытием ввода
#define CH_NME_EDIT_FIELD_H(z, x, y) NME_EDIT_FIELD(z, true, Constraints::x::##y##_ALLOWED_CHARS, Constraints::x::##y##_MIN_LENGTH, Constraints::x::##y##_MAX_LENGTH);

// Макрос для создания переменных доступа к элементам меню
#define CH_INIT auto menuElements = Menu::getActive()->getElements(); auto it = menuElements.begin();

// Макрос для смещения итератора (создан для соблюдения стиля)
#define CH_MOVE(x) it += x;

// Макрос для получения и проверки строки из текущего элемента, доступного по итератору
#define CH_CHECKED_GET(y, z, x) string x; x = ((MenuElementEditField *)(*it))->getInput(); if (x.length() < Constraints::y::##z##_MIN_LENGTH) { cout << "Длина поля " << (*it)->getText() << " не может быть меньше " << Constraints::y::##z##_MIN_LENGTH << " символов." << endl; system("pause"); return; }
