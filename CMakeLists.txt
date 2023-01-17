cmake_minimum_required(VERSION 3.12)

project(CTGL VERSION 1.0 LANGUAGES CXX)


add_library(${PROJECT_NAME} INTERFACE)

include(GNUInstallDirs)

target_include_directories(${PROJECT_NAME} INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/h/>
    $<INSTALL_INTERFACE:include>)


set(CMAKE_INSTALL_INCLUDEDIR "include/${PROJECT_NAME}")

include(CMakePackageConfigHelpers)

# Create version file
write_basic_package_version_file("${PROJECT_NAME}ConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion)

# Create a configuration file
configure_package_config_file(
    "${PROJECT_SOURCE_DIR}/cmake/config.cmake.in"
    "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/cmake/${PROJECT_NAME}
    PATH_VARS CMAKE_INSTALL_INCLUDEDIR)

# Install config and version files
install(FILES "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    "${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/cmake/${PROJECT_NAME})

# Define the install targets
install(TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}Targets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})


# Install the public headers
install(DIRECTORY src/h/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# Install the targets
install(EXPORT ${PROJECT_NAME}Targets
    FILE ${PROJECT_NAME}Targets.cmake
    NAMESPACE ${PROJECT_NAME}::
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/cmake/${PROJECT_NAME})
