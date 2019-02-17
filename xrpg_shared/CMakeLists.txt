add_subdirectory(src)

add_library(xrpg_shared ${src_files})

target_link_libraries(xrpg_shared PRIVATE portaudio_static cereal stdc++fs)

target_include_directories(xrpg_shared
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
        )
