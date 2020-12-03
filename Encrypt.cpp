#include "pch.h"
#include "Encrypt.h"
#include <algorithm>

namespace Utils
{
	string encrypt(string src)
	{
		reverse(src.begin(), src.end());
		string enc;
		for (char it : src)
		{
			enc += "X" + to_string((int)it);
		}
		return enc;
	}
}