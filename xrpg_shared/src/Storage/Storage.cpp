//
// Created by xgallom on 11. 2. 2019.
//

#include "Storage/Storage.h"

#include "Serialize.h"

#include <cereal/archives/binary.hpp>
#include <fstream>
#include <filesystem>

namespace Storage
{
	template<const char path[]>
	static Result<List> list()
	{
		std::vector<std::string> files;

		try {
			for(const auto &entry : std::filesystem::directory_iterator(path))
				files.push_back(entry.path().filename());
		} catch(std::exception &) {
			return Result<List>{};
		}

		return files;
	}

	template<typename T>
	static inline bool store(const std::string &fileName, const T &d)
	{
		std::fstream fstream(fileName, std::ios::out | std::ios::binary);

		OArchive archive(fstream);

		try { archive(d); } catch(...) { return false; }

		return true;
	}

	template<typename T>
	static inline Result<T> restore(const std::string &fileName)
	{
		std::fstream fstream(fileName, std::ios::in | std::ios::binary);

		IArchive archive(fstream);

		T d;

		try { archive(d); } catch(...) { return {}; }

		return d;
	}

	namespace Save {
		static constexpr char path[] = "data/save/";
		Result<List> list() { return ::Storage::list<path>(); }
		bool store(const ::Save &save) { return ::Storage::store("save.bin", save); }
		Result<::Save> restore(const std::string &save) { return ::Storage::restore<::Save>(path + save); }
	}

	namespace Level {
		static constexpr char path[] = "data/level/";
		Result<List> list() { return ::Storage::list<path>(); }
		bool store(const std::string &fileName, const ::Level &level)
		{ return ::Storage::store(path + fileName, level); }
		Result<::Level> restore(const std::string &fileName)
		{ return ::Storage::restore<::Level>(path + fileName); }
	}

	namespace Settings {
		static constexpr char fileName[] = "data/config.bin";
		bool store(const ::Settings &settings) { return ::Storage::store(fileName, settings); }
		Result<::Settings> restore() { return Storage::restore<::Settings>(fileName); }
	}

	namespace Music {
		static constexpr char path[] = "data/music/";
		std::string fileNameFor(::Music::Enum music) {
			static constexpr char fileNames[::Music::Size][15] = {
				"wilderness.wav",
				"rogue.wav",
				"sisters.wav",
				"spider.wav",
				"jungle.wav",
				"zakarum.wav",
				"desert.wav",
				"toru.wav",
				"sanctuary.wav",
				"crypt.wav",
				"tombs.wav",
				"monastery.wav",
				"cave.wav",
				"mesa.wav",
				"leoric.wav",
				"coda.wav",
				"roger.wav",
				"ancients.wav",
				"docks.wav",
				"fortress.wav",
				"halls.wav",
				"ice.wav",
				"kurast.wav",
				"maggot.wav",
				"mephisto.wav",
				"sewer.wav",
				"siege.wav",
				"title.wav",
				"tristram.wav"
			};

			return std::string(path) + fileNames[music];
		}
	}
}