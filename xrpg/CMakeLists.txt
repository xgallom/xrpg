add_subdirectory(src)

add_executable(xrpg ${src_files})

target_include_directories(xrpg
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
        )

target_link_libraries(xrpg PRIVATE xrpg_shared)
