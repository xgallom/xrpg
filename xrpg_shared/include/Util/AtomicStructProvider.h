//
// Created by xgallom on 2/17/19.
//

#ifndef XRPG_ATOMICSTRUCTPROVIDER_H
#define XRPG_ATOMICSTRUCTPROVIDER_H

#include "Result.h"

#include <atomic>

template<typename T>
class AtomicStructProvider {
public:

private:
	std::atomic<T *> m_data;
};

#endif //XRPG_ATOMICSTRUCTPROVIDER_H
