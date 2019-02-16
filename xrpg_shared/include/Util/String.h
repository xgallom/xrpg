//
// Created by xgallom on 12. 2. 2019.
//

#ifndef XRPG_STRING_H
#define XRPG_STRING_H

#include <string>

namespace String
{
	constexpr auto strlen(const char *str) {
		const char *i = str;
		while(*i) { ++i; }
		return static_cast<size_t>(i - str);
	}

	constexpr bool isLower(int input) { return input >= 'a' && input <= 'z'; }
	constexpr bool isUpper(int input) { return input >= 'A' && input <= 'Z'; }
	constexpr bool isChar (int input) { return isLower(input) || isUpper(input); }
	constexpr bool isNum  (int input) { return input >= '0' && input <= '9'; }
	constexpr bool isHex  (int input) { return isNum(input) || (input >= 'a' && input <= 'f'); }
	constexpr bool isFile (int input) { return isChar(input) || isNum(input) || input == '.'; }

	constexpr int  fromHex(int input) { return isNum(input) ? input - '0' : input - 'a'; }

	template<size_t MaxSize, bool ... Cmps (int)>
	inline void update(std::string &str, int input)
	{
		if(input == '\b' || input == '\x7f') {
			if(!str.empty())
				str.pop_back();
		}
		else if((Cmps(input) || ...) && str.size() < MaxSize)
			str.push_back(input);
	}
}

#endif //XRPG_STRING_H
