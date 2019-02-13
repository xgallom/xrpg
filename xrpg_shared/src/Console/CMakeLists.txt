set(src ${CMAKE_CURRENT_SOURCE_DIR})

if(WIN32)
    set(native ${src}/win32.cpp)
else()
    set(native ${src}/ansi.cpp)
endif()

set(Console
        ${native}
        ${src}/generic.cpp

        PARENT_SCOPE
        )