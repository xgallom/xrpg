set(src ${CMAKE_CURRENT_SOURCE_DIR})

if(WIN32)
    set(CONSOLE_SRC ${src}/win32.cpp)
else()
    set(CONSOLE_SRC ${src}/ansi.cpp)
endif()

set(Console
        ${CONSOLE_SRC}

        PARENT_SCOPE
        )