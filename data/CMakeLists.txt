
set(src ${CMAKE_CURRENT_SOURCE_DIR})
set(bin ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/data)

add_custom_target(data ALL)

add_custom_command(TARGET data POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory ${bin}/music ${bin}/sound
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${src}/music/* ${bin}/music/
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${src}/sound/* ${bin}/sound/
        )
