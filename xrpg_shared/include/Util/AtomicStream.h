//
// Created by xgallom on 2/18/19.
//

#ifndef XRPG_ATOMICSTREAM_H
#define XRPG_ATOMICSTREAM_H

#include "Result.h"
#include "AtomicBuffer.h"

#include <memory>

template<typename T>
class AtomicStream {
public:
	using value_type = T;
	static constexpr auto
			IndexBitOffset = 10,
			IndexBitMask = IndexBitOffset - 1;
	static constexpr auto MaxSize = 1 << IndexBitOffset /* 1024 */;

	AtomicStream() = default;

	bool canPublish()
	{
		m_writerCache.index = m_end.load(std::memory_order_relaxed);
		m_writerCache.nextIndex = AtomicContainer::advance<MaxSize>(m_writerCache.index);

		return m_writerCache.nextIndex != m_writerCache.notCleaned;
	}

	void publish(std::unique_ptr<value_type> &&value)
	{
		m_data[m_writerCache.index] = std::move(value);

		m_end.store(m_writerCache.nextIndex, std::memory_order_release);
	}

	void cleanUp()
	{
		size_t begin = m_begin.load(std::memory_order_acquire);

		while(m_writerCache.notCleaned != begin) {
			m_data[m_writerCache.notCleaned].reset();
			m_writerCache.notCleaned = AtomicContainer::advance<MaxSize>(m_writerCache.notCleaned);
		}
	}

	Result<const value_type *> tryAcquire()
	{
		const size_t end = m_end.load(std::memory_order_acquire);
		m_readerCache.begin = m_begin.load(std::memory_order_relaxed);

		if(m_readerCache.begin == end)
			return {};

		return m_data[m_readerCache.begin].get();
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
				notCleaned = 0,
				index = 0,
				nextIndex = 0;
	} m_writerCache = {};

	std::atomic<size_t> m_begin = 0;
	std::atomic<size_t> m_end = 0;
	std::array<std::unique_ptr<value_type>, MaxSize> m_data = {};
};

#endif //XRPG_ATOMICSTREAM_H
