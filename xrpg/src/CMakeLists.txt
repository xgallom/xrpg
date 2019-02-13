add_subdirectory(Context)
add_subdirectory(Run)

set(src ${CMAKE_CURRENT_SOURCE_DIR})

set(src_files
        ${Context}
        ${Run}

        ${src}/main.cpp

        PARENT_SCOPE
        )
