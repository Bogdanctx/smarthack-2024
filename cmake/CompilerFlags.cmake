###############################################################################

# custom compiler flags
message("Compiler: ${CMAKE_CXX_COMPILER_ID} version ${CMAKE_CXX_COMPILER_VERSION}")
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /permissive- /wd4244 /wd4267 /wd4996 /external:anglebrackets /external:W0 /utf-8 /MP)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic)
endif()

###############################################################################

# sanitizers

if("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU")
else()
    set_custom_stdlib_and_sanitizers(sfml-system false)
    set_custom_stdlib_and_sanitizers(sfml-window false)
    set_custom_stdlib_and_sanitizers(sfml-graphics false)
    set_custom_stdlib_and_sanitizers(sfml-audio false)
endif()

set_custom_stdlib_and_sanitizers(${PROJECT_NAME} true)
