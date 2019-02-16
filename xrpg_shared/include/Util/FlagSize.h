//
// Created by xgallom on 2/15/19.
//

#ifndef XRPG_FLAGSIZE_H
#define XRPG_FLAGSIZE_H

#include <cstdint>

namespace Flag
{
	using flag_type = uint8_t;

	using value_type8 = uint8_t;
	using value_type16 = uint16_t;
	using value_type32 = uint32_t;
	using value_type64 = uint64_t;

	template<flag_type Size> struct FlagsSize { static_assert(Size <= 64, "Flag object can hold at max 64 flags"); };

	template<> struct FlagsSize< 0> { using value_type = value_type8 ; };
	template<> struct FlagsSize< 1> { using value_type = value_type8 ; };
	template<> struct FlagsSize< 2> { using value_type = value_type8 ; };
	template<> struct FlagsSize< 3> { using value_type = value_type8 ; };
	template<> struct FlagsSize< 4> { using value_type = value_type8 ; };
	template<> struct FlagsSize< 5> { using value_type = value_type8 ; };
	template<> struct FlagsSize< 6> { using value_type = value_type8 ; };
	template<> struct FlagsSize< 7> { using value_type = value_type8 ; };
	template<> struct FlagsSize< 8> { using value_type = value_type8 ; };
	template<> struct FlagsSize< 9> { using value_type = value_type16; };
	template<> struct FlagsSize<10> { using value_type = value_type16; };
	template<> struct FlagsSize<11> { using value_type = value_type16; };
	template<> struct FlagsSize<12> { using value_type = value_type16; };
	template<> struct FlagsSize<13> { using value_type = value_type16; };
	template<> struct FlagsSize<14> { using value_type = value_type16; };
	template<> struct FlagsSize<15> { using value_type = value_type16; };
	template<> struct FlagsSize<16> { using value_type = value_type16; };
	template<> struct FlagsSize<17> { using value_type = value_type32; };
	template<> struct FlagsSize<18> { using value_type = value_type32; };
	template<> struct FlagsSize<19> { using value_type = value_type32; };
	template<> struct FlagsSize<20> { using value_type = value_type32; };
	template<> struct FlagsSize<21> { using value_type = value_type32; };
	template<> struct FlagsSize<22> { using value_type = value_type32; };
	template<> struct FlagsSize<23> { using value_type = value_type32; };
	template<> struct FlagsSize<24> { using value_type = value_type32; };
	template<> struct FlagsSize<25> { using value_type = value_type32; };
	template<> struct FlagsSize<26> { using value_type = value_type32; };
	template<> struct FlagsSize<27> { using value_type = value_type32; };
	template<> struct FlagsSize<28> { using value_type = value_type32; };
	template<> struct FlagsSize<29> { using value_type = value_type32; };
	template<> struct FlagsSize<30> { using value_type = value_type32; };
	template<> struct FlagsSize<31> { using value_type = value_type32; };
	template<> struct FlagsSize<32> { using value_type = value_type32; };
	template<> struct FlagsSize<33> { using value_type = value_type64; };
	template<> struct FlagsSize<34> { using value_type = value_type64; };
	template<> struct FlagsSize<35> { using value_type = value_type64; };
	template<> struct FlagsSize<36> { using value_type = value_type64; };
	template<> struct FlagsSize<37> { using value_type = value_type64; };
	template<> struct FlagsSize<38> { using value_type = value_type64; };
	template<> struct FlagsSize<39> { using value_type = value_type64; };
	template<> struct FlagsSize<40> { using value_type = value_type64; };
	template<> struct FlagsSize<41> { using value_type = value_type64; };
	template<> struct FlagsSize<42> { using value_type = value_type64; };
	template<> struct FlagsSize<43> { using value_type = value_type64; };
	template<> struct FlagsSize<44> { using value_type = value_type64; };
	template<> struct FlagsSize<45> { using value_type = value_type64; };
	template<> struct FlagsSize<46> { using value_type = value_type64; };
	template<> struct FlagsSize<47> { using value_type = value_type64; };
	template<> struct FlagsSize<48> { using value_type = value_type64; };
	template<> struct FlagsSize<49> { using value_type = value_type64; };
	template<> struct FlagsSize<50> { using value_type = value_type64; };
	template<> struct FlagsSize<51> { using value_type = value_type64; };
	template<> struct FlagsSize<52> { using value_type = value_type64; };
	template<> struct FlagsSize<53> { using value_type = value_type64; };
	template<> struct FlagsSize<54> { using value_type = value_type64; };
	template<> struct FlagsSize<55> { using value_type = value_type64; };
	template<> struct FlagsSize<56> { using value_type = value_type64; };
	template<> struct FlagsSize<57> { using value_type = value_type64; };
	template<> struct FlagsSize<58> { using value_type = value_type64; };
	template<> struct FlagsSize<59> { using value_type = value_type64; };
	template<> struct FlagsSize<60> { using value_type = value_type64; };
	template<> struct FlagsSize<61> { using value_type = value_type64; };
	template<> struct FlagsSize<62> { using value_type = value_type64; };
	template<> struct FlagsSize<63> { using value_type = value_type64; };
	template<> struct FlagsSize<64> { using value_type = value_type64; };
}

#endif //XRPG_FLAGSIZE_H
