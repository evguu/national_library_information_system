#include "pch.h"
#include "Person.h"

namespace Constraints
{
	namespace Person
	{
		const int FULL_NAME_MIN_LENGTH = 6;
		const int FULL_NAME_MAX_LENGTH = 64;
		const string FULL_NAME_ALLOWED_CHARS = CharacterSets::RUSSIAN + " -";
	}
};
