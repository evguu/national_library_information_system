#include "pch.h"
#include <string>
#include <locale>
#include "Input.h"
#include <iostream>
using namespace std;

namespace Utils
{
	// �������� �������: https://www.cyberforum.ru/cpp-beginners/thread1840198.html#post9717879
	// ������������ ��� �������� ������� �������� � ������� � ������ ������� ���������.
	// �� ������ ������ �� ������������.
	std::string ws2s(const std::wstring& wstr, const std::locale& loc)
	{
		if (wstr.empty())
			return std::string();

		typedef std::wstring::traits_type::state_type state_type;
		typedef std::codecvt<wchar_t, char, state_type> convert;

		const convert& cvt = std::use_facet<convert>(loc);
		std::string str(cvt.max_length()*wstr.size(), '\0');
		state_type state = state_type();

		const wchar_t* from_beg = &wstr[0];
		const wchar_t* from_end = from_beg + wstr.size();
		const wchar_t* from_nxt;
		char* to_beg = &str[0];
		char* to_end = to_beg + str.size();
		char* to_nxt;

		std::string::size_type sz = 0;
		std::codecvt_base::result r;
		do
		{
			r = cvt.out(state, from_beg, from_end, from_nxt,
				to_beg, to_end, to_nxt);
			switch (r)
			{
			case std::codecvt_base::error:
				throw std::runtime_error("error converting wstring to string");

			case std::codecvt_base::partial:
				sz += to_nxt - to_beg;
				str.resize(2 * str.size());
				to_beg = &str[sz];
				to_end = &str[0] + str.size();
				break;

			case std::codecvt_base::noconv:
				str.resize(sz + (from_end - from_beg) * sizeof(wchar_t));
				std::memcpy(&str[sz], from_beg, (from_end - from_beg) * sizeof(wchar_t));
				r = std::codecvt_base::ok;
				break;

			case std::codecvt_base::ok:
				sz += to_nxt - to_beg;
				str.resize(sz);
				break;
			}
		} while (r != std::codecvt_base::ok);

		return str;
	}

	// ��������� ������� ������ � �������.
	char wc2c(wchar_t w)
	{
		switch (w)
		{
		case L'q':
			return 'q';
		case L'w':
			return 'w';
		case L'e':
			return 'e';
		case L'r':
			return 'r';
		case L't':
			return 't';
		case L'y':
			return 'y';
		case L'u':
			return 'u';
		case L'i':
			return 'i';
		case L'o':
			return 'o';
		case L'p':
			return 'p';
		case L'a':
			return 'a';
		case L's':
			return 's';
		case L'd':
			return 'd';
		case L'f':
			return 'f';
		case L'g':
			return 'g';
		case L'h':
			return 'h';
		case L'j':
			return 'j';
		case L'k':
			return 'k';
		case L'l':
			return 'l';
		case L'z':
			return 'z';
		case L'x':
			return 'x';
		case L'c':
			return 'c';
		case L'v':
			return 'v';
		case L'b':
			return 'b';
		case L'n':
			return 'n';
		case L'm':
			return 'm';
		case L'Q':
			return 'Q';
		case L'W':
			return 'W';
		case L'E':
			return 'E';
		case L'R':
			return 'R';
		case L'T':
			return 'T';
		case L'Y':
			return 'Y';
		case L'U':
			return 'U';
		case L'I':
			return 'I';
		case L'O':
			return 'O';
		case L'P':
			return 'P';
		case L'A':
			return 'A';
		case L'S':
			return 'S';
		case L'D':
			return 'D';
		case L'F':
			return 'F';
		case L'G':
			return 'G';
		case L'H':
			return 'H';
		case L'J':
			return 'J';
		case L'K':
			return 'K';
		case L'L':
			return 'L';
		case L'Z':
			return 'Z';
		case L'X':
			return 'X';
		case L'C':
			return 'C';
		case L'V':
			return 'V';
		case L'B':
			return 'B';
		case L'N':
			return 'N';
		case L'M':
			return 'M';
		case L'�':
			return '�';
		case L'�':
			return '�';
		case L'�':
			return '�';
		case L'�':
			return '�';
		case L'�':
			return '�';
		case L'�':
			return '�';
		case L'�':
			return '�';
		case L'�':
			return '�';
		case L'�':
			return '�';
		case L'�':
			return '�';
		case L'�':
			return '�';
		case L'�':
			return '�';
		case L'�':
			return '�';
		case L'�':
			return '�';
		case L'�':
			return '�';
		case L'�':
			return '�';
		case L'�':
			return '�';
		case L'�':
			return '�';
		case L'�':
			return '�';
		case L'�':
			return '�';
		case L'�':
			return '�';
		case L'�':
			return '�';
		case L'�':
			return '�';
		case L'�':
			return '�';
		case L'�':
			return '�';
		case L'�':
			return '�';
		case L'�':
			return '�';
		case L'�':
			return '�';
		case L'�':
			return '�';
		case L'�':
			return '�';
		case L'�':
			return '�';
		case L'�':
			return '�';
		case L'�':
			return '�';
		case L'�':
			return '�';
		case L'�':
			return '�';
		case L'�':
			return '�';
		case L'�':
			return '�';
		case L'�':
			return '�';
		case L'�':
			return '�';
		case L'�':
			return '�';
		case L'�':
			return '�';
		case L'�':
			return '�';
		case L'�':
			return '�';
		case L'�':
			return '�';
		case L'�':
			return '�';
		case L'�':
			return '�';
		case L'�':
			return '�';
		case L'�':
			return '�';
		case L'�':
			return '�';
		case L'�':
			return '�';
		case L'�':
			return '�';
		case L'�':
			return '�';
		case L'�':
			return '�';
		case L'�':
			return '�';
		case L'�':
			return '�';
		case L'�':
			return '�';
		case L'�':
			return '�';
		case L'�':
			return '�';
		case L'�':
			return '�';
		case L'�':
			return '�';
		case L'�':
			return '�';
		case L'�':
			return '�';
		case L'�':
			return '�';
		case L'�':
			return '�';
		case L'0':
			return '0';
		case L'1':
			return '1';
		case L'2':
			return '2';
		case L'3':
			return '3';
		case L'4':
			return '4';
		case L'5':
			return '5';
		case L'6':
			return '6';
		case L'7':
			return '7';
		case L'8':
			return '8';
		case L'9':
			return '9';
		case L'�':
			return '�';
		case L'�':
			return '�';
		case L'~':
			return '~';
		case L'!':
			return '!';
		case L'@':
			return '@';
		case L'#':
			return '#';
		case L'$':
			return '$';
		case L'%':
			return '%';
		case L'^':
			return '^';
		case L'&':
			return '&';
		case L'*':
			return '*';
		case L'(':
			return '(';
		case L')':
			return ')';
		case L'_':
			return '_';
		case L'+':
			return '+';
		case L'-':
			return '-';
		case L'=':
			return '=';
		case L'[':
			return '[';
		case L']':
			return ']';
		case L'{':
			return '{';
		case L'}':
			return '}';
		case L';':
			return ';';
		case L':':
			return ':';
		case L'\'':
			return '\'';
		case L'"':
			return '"';
		case L',':
			return ',';
		case L'.':
			return '.';
		case L'/':
			return '/';
		case L'?':
			return '?';
		case L' ':
			return ' ';
		default:
			return '?';
		}
	}

	// ���������� ������������� ���, ���� ������ ������. ������������� ���, ���� ������� ��������� �������.
	int inputKeyEvent()
	{
		wchar_t wide;
		wide = _getwch();
		//wide = wcin.get();

		switch (wide)
		{
		case KC_ARROW_INCOMING:
			return -_getwch();
		case KC_TAB:
			return -KC_TAB;
		case KC_DELETE:
			return -KC_DELETE;
		case KC_BACKSPACE:
			return -KC_BACKSPACE;
		case KC_ENTER:
			return -KC_ENTER;
		}

		unsigned char char_value = wc2c(wide);
		return char_value;
	}
}