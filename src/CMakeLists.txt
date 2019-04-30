cmake_minimum_required(VERSION 3.11)
project(cbloxfull)

include(GNUInstallDirs)

find_package(curl)
add_library(curl SHARED IMPORTED)
set_target_properties(curl PROPERTIES
        IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/libs/curl/libcurl.dll"
        INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/libs"
        )

add_subdirectory(cblox)