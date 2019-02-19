//
// Created by xgallom on 2/19/19.
//

#ifndef XRPG_AUDIOCONTEXT_H
#define XRPG_AUDIOCONTEXT_H

#include <atomic>

class Settings;

namespace Audio
{
	namespace AudioContext
	{
		struct AudioLevels {
			static constexpr int
				Min = 0,
				Max = 100;

			std::atomic<int>
					master = 100,
					music  = 100,
					sound  = 100;

			void apply(const Settings &settings);
		};

		AudioLevels &audioLevels();
	}
}

#endif //XRPG_AUDIOCONTEXT_H
