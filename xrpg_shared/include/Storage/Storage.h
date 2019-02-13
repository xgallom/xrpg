//
// Created by xgallom on 11. 2. 2019.
//

#ifndef XRPG_STORAGE_H
#define XRPG_STORAGE_H

#include "Save.h"

namespace Storage
{
	template<typename T>
	struct Result {
		bool ok = false;
		T value = T{};

		constexpr Result() = default;
		constexpr Result(const T &v) : ok{true}, value{v} {}
		constexpr Result(T &&v) : ok{true}, value{std::move(v)} {}

		constexpr T &operator()() { return value; }
		constexpr const T &operator()() const { return value; }
		constexpr operator bool() const { return ok; }
	};

	namespace Save {
		bool store(const ::Save &save);
		Result<::Save> restore();
	}
}

#endif //XRPG_STORAGE_H
