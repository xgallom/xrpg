//
// Created by xgallom on 12. 2. 2019.
//

#ifndef XRPG_STRING_H
#define XRPG_STRING_H

#include <string>

namespace String
{
	constexpr bool isLower(int input) { return input >= 'a' && input <= 'z'; }
	constexpr bool isUpper(int input) { return input >= 'A' && input <= 'Z'; }
	constexpr bool isChar (int input) { return isLower(input) || isUpper(input); }
	constexpr bool isNum  (int input) { return input >= '0' && input <= '9'; }

	template<size_t MaxSize, bool ... Cmps (int)>
	inline void update(std::string &str, int input)
	{
		if(input == '\b' || input == '\x7f') {
			if(!str.empty())
				str.pop_back();
		}
		else if((Cmps(input) && ...) && str.size() < MaxSize)
			str.push_back(input);
	}
}

#endif //XRPG_STRING_H
