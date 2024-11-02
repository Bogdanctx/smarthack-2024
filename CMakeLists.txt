cmake_minimum_required(VERSION 3.26)

project(sfml-template)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(cmake/Options.cmake)

###############################################################################

# external dependencies with FetchContent

include(FetchContent)

set(FETCHCONTENT_QUIET OFF)
set(FETCHCONTENT_UPDATES_DISCONNECTED ON)


FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG        2.6.1
    GIT_SHALLOW    1
)
FetchContent_MakeAvailable(SFML)


FetchContent_Declare(
        cpr
        GIT_REPOSITORY https://github.com/libcpr/cpr.git
        GIT_TAG 1.11.0
)
FetchContent_MakeAvailable(cpr)

FetchContent_Declare(
        json
        GIT_REPOSITORY https://github.com/nlohmann/json
        GIT_TAG v3.11.3
)
FetchContent_MakeAvailable(json)

###############################################################################

# external dependencies with find_package

find_package(Threads REQUIRED)
if(APPLE)
elseif(UNIX)
    find_package(X11)
endif()

###############################################################################

add_executable(${PROJECT_NAME}
    main.cpp
    Engine.cpp
    Engine.h
    ResourceManager.cpp
    ResourceManager.h
        main.cpp
        Engine.cpp
        Engine.h
        Engine.h
        ResourceManager.h
        ResourceManager.cpp
)

###############################################################################

target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ${SFML_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ${cpr_SOURCE_DIR}/include)
target_link_directories(${PROJECT_NAME} PRIVATE ${SFML_BINARY_DIR}/lib)
target_link_libraries(
        ${PROJECT_NAME} PRIVATE
        sfml-graphics
        sfml-window
        sfml-audio
        sfml-system
        cpr::cpr
        nlohmann_json::nlohmann_json
        Threads::Threads)

if(UNIX)
    target_link_libraries(${PROJECT_NAME} PRIVATE X11)
endif()

###############################################################################

# copy binaries to "bin" folder; these are uploaded as artifacts on each release
# DESTINATION_DIR is set as "bin" in cmake/Options.cmake:6
install(TARGETS ${PROJECT_NAME} DESTINATION ${DESTINATION_DIR})
if(APPLE)
    install(FILES launcher.command DESTINATION ${DESTINATION_DIR})
endif()

# copy dependent DLLs to build dir
# see https://en.sfml-dev.org/forums/index.php?topic=28580.0
# remove this if not using audio or if using SFML 3
if (WIN32 AND SFML_BUILD_AUDIO)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_if_different
         ${SFML_SOURCE_DIR}/extlibs/bin/x64/openal32.dll
         $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )
endif()


include(cmake/CopyHelper.cmake)
copy_files(DIRECTORY resources)
