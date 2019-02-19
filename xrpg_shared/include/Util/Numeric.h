//
// Created by xgallom on 12. 2. 2019.
//

#ifndef XRPG_NUMERIC_H
#define XRPG_NUMERIC_H

namespace Numeric
{
	template<typename T, T Min, T Max>
	inline void update(T &v, int input, T &remaining)
	{
		if(input == '4' && v > Min) {
			--v;
			++remaining;
		}
		else if(input == '6' && v < Max && remaining) {
			++v;
			--remaining;
		}
	}

	template<typename T, T Min, T Max, T Step>
	inline void updateWithStep(T &v, int input)
	{
		if(input == '4') {
			const auto newValue = v - Step;

			if(newValue < Min)
				v = Min;
			else
				v = newValue;
		}
		else if(input == '6') {
			const auto newValue = v + Step;

			if(newValue > Max)
				v = Max;
			else
				v = newValue;
		}
	}

	template<typename T, T Min, T Max>
	inline void update(T &v, int input)
	{
		if(input == '\b' || input == '\x7f') {
			const auto newValue = v / 10;

			if(newValue >= Min)
				v = newValue;
		}
		else if(input >= '0' && input <= '9') {
			const auto newValue = v * 10 + (input - '0');

			if(newValue <= Max)
				v = newValue;
		}
	}
}

#endif //XRPG_NUMERIC_H
