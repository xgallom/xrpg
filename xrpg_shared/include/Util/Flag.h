//
// Created by xgallom on 2/15/19.
//

#ifndef XRPG_FLAG_H
#define XRPG_FLAG_H

#include "FlagSize.h"

namespace Flag
{
	constexpr auto maskFor(flag_type flag) { return 1 << flag; }

	template<flag_type flag>
	struct Flag {
		static constexpr auto value = flag;
		static constexpr auto mask = maskFor(flag);
	};

	template<flag_type Size>
	struct FlagsValues {
		using value_type = typename FlagsSize<Size>::value_type;

		value_type values = 0;

		template<flag_type ... flags>
		value_type expand() { return (Flag<flags>::mask | ...); }

		template<flag_type ... flags>
		void set() { values |= expand<flags ...>(); }

		template<flag_type ... flags>
		void unset() { values &= expand<flags ...>(); }

		template<flag_type ... flags>
		bool isSet() { return (values & expand<flags ...>()) != 0; }
	};
}

#endif //XRPG_FLAG_H
