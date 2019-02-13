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
}

#endif //XRPG_NUMERIC_H
