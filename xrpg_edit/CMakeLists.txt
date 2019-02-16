add_subdirectory(src)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-exceptions")

add_executable(xrpg_edit ${src_files})

target_include_directories(xrpg_edit
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
        )

target_link_libraries(xrpg_edit PRIVATE xrpg_shared)
