 //
// Created by xgallom on 11. 2. 2019.
//

#ifndef XRPG_STORAGE_H
#define XRPG_STORAGE_H

#include "Save.h"
#include "Level.h"

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

	using List = std::vector<std::string>;

	namespace Save {
		Result<List> list();
		bool store(const ::Save &save);
		Result<::Save> restore(const std::string &save);
	}

	namespace Level {
		bool store(const std::string &fileName, const ::Level &level);
		Result<::Level> restore(const std::string &fileName);
	}
}

#endif //XRPG_STORAGE_H
