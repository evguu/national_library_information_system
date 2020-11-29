#include "pch.h"
#include "CharacterSets.h"

namespace Constraints
{
	namespace CharacterSets
	{
		const string ENGLISH_LOWER = "qwertyuiopasdfghjklzxcvbnm"s;
		const string ENGLISH_UPPER = "QWERTYUIOPASDFGHJKLZXCVBNM"s;
		const string ENGLISH = ENGLISH_LOWER + ENGLISH_UPPER;
		const string RUSSIAN_LOWER = "��������������������������������"s;
		const string RUSSIAN_UPPER = "��������������������������������"s;
		const string RUSSIAN = RUSSIAN_LOWER + RUSSIAN_UPPER;
		const string NUMBERS = "0123456789"s;
		const string EXTENDED = ENGLISH + RUSSIAN + NUMBERS + " -_&+."s;
	}
}
