//
// Created by xgallom on 10. 2. 2019.
//

#include "Run.h"

#include "MainMenu.h"
#include "NewGame.h"
#include "LoadGame.h"
#include "LoadLevel.h"

#include "Context/GlobalContext.h"

#include <Audio/Audio.h>
#include <Audio/AudioStream.h>
#include <Graphics/OutputBuffer.h>
#include <Run/Dispatch.h>
#include <iostream>
#include <chrono>
#include <thread>

namespace Run
{
	static void synchronize();

	bool init(const Arguments &arguments)
	{
		bool enableDebug = false;
		for(const auto &argument : arguments) {
			if(argument == "ENABLE_DEBUG")
				enableDebug = true;
			else {
				std::cerr << "Invalid argument " << argument << "\n";
				return false;
			}
		}

		return
			OutputBuffer::init({80, 25}, enableDebug) &&
			Audio::init() &&
			Audio::openDefaultStream() &&
			Audio::startStream();
	}

	bool run()
	{
		static constexpr bool (* const runTable[GlobalState::Size]) (void) = {
				&dispatch<MainMenu >,
				&dispatch<NewGame  >,
				&dispatch<LoadGame >,
				&dispatch<LoadLevel>,
				&dispatchQuit
		};

		synchronize();

		return (*runTable[GlobalContext::state()])();
	}

	void deinit()
	{
		OutputBuffer::deinit();
		Audio::deinit();
	}

	static void synchronize()
	{
		static auto lastUpdate = std::chrono::high_resolution_clock::now();

		auto now = std::chrono::high_resolution_clock::now();

		std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 30) - (now - lastUpdate));

		lastUpdate = now;
	}
}