#pragma once
#include <string>
#include <locale>
#define KC_ARROW_INCOMING 224
#define KC_UP 72
#define KC_DOWN 80
#define KC_LEFT 75
#define KC_RIGHT 77
#define KC_DELETE 83
#define KC_BACKSPACE 8
#define KC_TAB 9
#define KC_ENTER 13

namespace Utils
{
	std::string ws2s(const std::wstring& wstr, const std::locale& loc);
	int inputKeyEvent();
}