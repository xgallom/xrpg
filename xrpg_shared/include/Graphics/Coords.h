//
// Created by xgallom on 10. 2. 2019.
//

#ifndef XRPG_COORDS_H
#define XRPG_COORDS_H

struct Coords {
	using value_type = unsigned short;

	value_type x = 0, y = 0;

	constexpr Coords &operator+=(const Coords &r) { x += r.x; y += r.y; return *this; }
	constexpr Coords &operator-=(const Coords &r) { x -= r.x; y -= r.y; return *this; }
	constexpr Coords &operator*=(value_type r) { x *= r; y *= r; return *this; }
	constexpr Coords &operator/=(value_type r) { x /= r; y /= r; return *this; }

	constexpr bool operator==(const Coords &r) { return x == r.x && y == r.y; }
	constexpr bool operator!=(const Coords &r) { return !(*this == r); }
};

constexpr Coords operator+(Coords l, const Coords &r) { return l += r; }
constexpr Coords operator-(Coords l, const Coords &r) { return l -= r; }
constexpr Coords operator*(Coords l, Coords::value_type r) { return l *= r; }
constexpr Coords operator/(Coords l, Coords::value_type r) { return l /= r; }

constexpr Coords center(Coords c1, Coords c2) { return (c1 - c2) / 2; }

struct Region {
	Coords tl, br;

	constexpr Coords size() const { return br - tl; }
};

#endif //XRPG_COORDS_H