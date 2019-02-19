//
// Created by xgallom on 2/17/19.
//

#ifndef XRPG_ATOMICSTRUCT_H
#define XRPG_ATOMICSTRUCT_H

#include <atomic>

template<typename T>
class AtomicStruct {
public:
	using value_type = T;

	AtomicStruct(const value_type &defaultValue) : m_data(new value_type(defaultValue)) {}

	const value_type get() const { return m_data.load(std::memory_order_acquire); }
	void set(const value_type &value) { m_data.store(value, std::memory_order_release); }

private:
	std::atomic<value_type> m_data;
};

#endif //XRPG_ATOMICSTRUCT_H
