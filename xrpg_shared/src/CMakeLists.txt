set(src ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(Console)
add_subdirectory(Data)
add_subdirectory(Graphics)
add_subdirectory(Storage)
add_subdirectory(Util)

set(src_files
        ${Console}
        ${Data}
        ${Graphics}
        ${Storage}
        ${Util}

        PARENT_SCOPE
        )
