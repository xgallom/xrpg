set(src ${CMAKE_CURRENT_SOURCE_DIR})

set(Audio
        ${src}/Data/WavFileBuffer.cpp
        ${src}/Data/WavFile.cpp
        ${src}/Data/WavFileStream.cpp
        ${src}/Audio.cpp
        ${src}/AudioCallback.cpp
        ${src}/AudioContext.cpp
        ${src}/AudioPlayer.cpp
        ${src}/AudioProcessing.cpp
        ${src}/AudioStream.cpp
        ${src}/AudioThread.cpp

        PARENT_SCOPE
        )