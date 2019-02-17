//
// Created by xgallom on 2/17/19.
//

#ifndef XRPG_RESULT_H
#define XRPG_RESULT_H

#include <utility>

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

#endif //XRPG_RESULT_H
