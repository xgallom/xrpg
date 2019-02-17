
set(src ${CMAKE_CURRENT_SOURCE_DIR})
set(bin ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/data)

add_custom_target(data ALL)

add_custom_command(TARGET data
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${src}/music ${bin}/music
        )

add_custom_command(TARGET data
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${src}/sound ${bin}/sound
        )