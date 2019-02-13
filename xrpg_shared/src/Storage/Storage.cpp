//
// Created by xgallom on 11. 2. 2019.
//

#include "Storage/Storage.h"

#include "Serialize.h"

#include <cereal/archives/binary.hpp>
#include <fstream>

namespace Storage
{
	template<typename T>
	static inline bool store(const char fileName[], const T &d)
	{
		std::fstream fstream(fileName, std::ios::out | std::ios::binary);

		OArchive archive(fstream);

		try { archive(d); } catch(cereal::Exception &) { return false; }

		return true;
	}

	template<typename T>
	static inline Result<T> restore(const char fileName[])
	{
		std::fstream fstream(fileName, std::ios::in | std::ios::binary);

		IArchive archive(fstream);

		T d;

		try { archive(d); } catch(cereal::Exception &) { return Result<T>{}; }

		return d;
	}

	namespace Save {
		bool store(const ::Save &save) { return ::Storage::store("save.bin", save); }
		Result<::Save> restore() { return ::Storage::restore<::Save>("save.bin"); }
	}

	namespace Level {
		bool store(const ::Level &level) { return ::Storage::store("map.bin", level); }
		Result<::Level> restore() { return ::Storage::restore<::Level>("map.bin"); }
	}
}