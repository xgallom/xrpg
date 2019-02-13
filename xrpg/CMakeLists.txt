add_subdirectory(src)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-exceptions")

add_executable(xrpg ${src_files})

target_include_directories(xrpg
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
        )

target_link_libraries(xrpg PRIVATE xrpg_shared)
