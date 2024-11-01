option(BUILD_SHARED_LIBS "Build SFML as shared library" FALSE)

set(DESTINATION_DIR "bin")

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "${PROJECT_SOURCE_DIR}/install_dir" CACHE PATH "..." FORCE)
endif()

set(is_debug "$<CONFIG:Debug>")
set(is_rel_with_deb "$<CONFIG:RelWithDebInfo>")
set(debug_mode "$<OR:${is_debug},${is_rel_with_deb}>")
