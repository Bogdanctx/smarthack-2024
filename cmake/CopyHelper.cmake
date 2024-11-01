function(copy_files)
    set(options OPTIONAL FAST)
    set(oneValueArgs DESTINATION)
    set(multiValueArgs FILES DIRECTORY)
    cmake_parse_arguments(PARSE_ARGV 0 ARG "${options}" "${oneValueArgs}" "${multiValueArgs}")

    # Copy files to build directory
    foreach(file ${ARG_FILES})
        add_custom_command(
                TARGET ${PROJECT_NAME} POST_BUILD
                COMMENT "Copying ${file}..."
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                ${CMAKE_SOURCE_DIR}/${file} $<TARGET_FILE_DIR:${PROJECT_NAME}>)
    endforeach()

    # Copy directories to build directory
    foreach(dir ${ARG_DIRECTORY})
        add_custom_command(
                TARGET ${PROJECT_NAME} POST_BUILD
                COMMENT "Copying directory ${dir}..."
                COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_SOURCE_DIR}/${dir} $<TARGET_FILE_DIR:${PROJECT_NAME}>/${dir})
    endforeach()

    # Install files and directories to install directory
    install(FILES ${ARG_FILES} DESTINATION ${DESTONATION_DIR})
    install(DIRECTORY ${ARG_DIRECTORY} DESTINATION ${DESTINATION_DIR})
endfunction()
