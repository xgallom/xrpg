//
// Created by xgallom on 2/18/19.
//

#ifndef XRPG_ATOMICBUFFER_H
#define XRPG_ATOMICBUFFER_H

#include "Result.h"

#include <array>
#include <atomic>

namespace AtomicContainer
{
	template<size_t MaxSize>
	static size_t advance(size_t index) { return ++index == MaxSize ? 0 : index; }
}

template<typename T>
class AtomicBuffer {
public:
	using value_type = T;
	static constexpr auto
		IndexBitOffset = 10,
		IndexBitMask = IndexBitOffset - 1;
	static constexpr auto MaxSize = 1 << IndexBitOffset /* 1024 */;

	AtomicBuffer() = default;

	bool canPublish()
	{
		size_t begin = m_begin.load(std::memory_order_acquire);

		m_writerCache.index = m_end.load(std::memory_order_relaxed);
		m_writerCache.nextIndex = AtomicContainer::advance<MaxSize>(m_writerCache.index);

		return m_writerCache.nextIndex != begin;
	}

	void publish(const value_type &value)
	{
		m_data[m_writerCache.index] = value;

		m_end.store(m_writerCache.nextIndex, std::memory_order_release);
	}

	Result<value_type> tryAcquire()
	{
		const size_t end = m_end.load(std::memory_order_acquire);
		m_readerCache.begin = m_begin.load(std::memory_order_relaxed);

		if(m_readerCache.begin == end)
			return {};

		return m_data[m_readerCache.begin];
	}

	void release()
	{
		m_begin.store(AtomicContainer::advance<MaxSize>(m_readerCache.begin), std::memory_order_release);
	}

private:
	struct {
		size_t begin = 0;
	} m_readerCache = {};

	struct {
		size_t
				index = 0,
				nextIndex = 0;
	} m_writerCache = {};

	std::atomic<size_t> m_begin = 0;
	std::atomic<size_t> m_end = 0;
	std::array<value_type, MaxSize> m_data = {};
};

#endif //XRPG_ATOMICBUFFER_H
