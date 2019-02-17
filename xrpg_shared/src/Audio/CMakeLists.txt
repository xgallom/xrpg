set(src ${CMAKE_CURRENT_SOURCE_DIR})

set(Audio
        ${src}/Data/File.cpp
        ${src}/Data/Stream.cpp
        ${src}/Audio.cpp
        ${src}/AudioContext.cpp
        ${src}/AudioStream.cpp
        ${src}/SampleFormat.cpp

        PARENT_SCOPE
        )