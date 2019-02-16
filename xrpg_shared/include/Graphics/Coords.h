//
// Created by xgallom on 10. 2. 2019.
//

#ifndef XRPG_COORDS_H
#define XRPG_COORDS_H

#include <cstddef>

template<typename _value_type>
struct GenericCoords {
	using value_type = _value_type;

	value_type x = 0, y = 0;

	constexpr size_t area() const { return static_cast<size_t>(x * y); }
	constexpr double aspect() const { return static_cast<double>(x) / static_cast<double>(y); }

	constexpr GenericCoords<value_type> &operator+=(const GenericCoords<value_type> &r)
	{ x += r.x; y += r.y; return *this; }
	constexpr GenericCoords<value_type> &operator-=(const GenericCoords<value_type> &r)
	{ x -= r.x; y -= r.y; return *this; }
	constexpr GenericCoords<value_type> &operator*=(value_type r) { x *= r; y *= r; return *this; }
	constexpr GenericCoords<value_type> &operator/=(value_type r) { x /= r; y /= r; return *this; }

	constexpr bool operator==(const GenericCoords<value_type> &r) const { return x == r.x && y == r.y; }
	constexpr bool operator!=(const GenericCoords<value_type> &r) const { return !(*this == r); }

	constexpr bool operator!() const { return !(x || y); }
};

template<typename v>
constexpr GenericCoords<v> operator+(GenericCoords<v> l, const GenericCoords<v> &r) { return l += r; }
template<typename v>
constexpr GenericCoords<v> operator-(GenericCoords<v> l, const GenericCoords<v> &r) { return l -= r; }
template<typename v>
constexpr GenericCoords<v> operator*(GenericCoords<v> l, typename GenericCoords<v>::value_type r) { return l *= r; }
template<typename v>
constexpr GenericCoords<v> operator/(GenericCoords<v> l, typename GenericCoords<v>::value_type r) { return l /= r; }

using Coords = GenericCoords<unsigned short>;

constexpr Coords::value_type center(Coords::value_type in, Coords::value_type v) { return (in - v) / 2; }
template<typename v>
constexpr GenericCoords<v> center(GenericCoords<v> in, GenericCoords<v> c) { return (in - c) / 2; }

template<typename T, typename U>
GenericCoords<T> transform(const GenericCoords<U> &from) {
	return GenericCoords<T>{static_cast<T>(from.x), static_cast<T>(from.y)};
}

struct Region {
	Coords tl, br;

	constexpr Coords size() const { return br - tl; }
};

struct IntCoords {

};

#endif //XRPG_COORDS_H
