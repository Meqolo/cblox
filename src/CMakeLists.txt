cmake_minimum_required(VERSION 3.11)
project(cbloxfull)

include(GNUInstallDirs)
ADD_DEFINITIONS( -DCURL_STATICLIB )

set( CURL_LIBRARY ${CMAKE_SOURCE_DIR}/libs/curl/lib )
set( CURL_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/libs/curl/include )
find_package(curl)
add_library(curl SHARED IMPORTED)
set_target_properties(curl PROPERTIES
        IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/libs/curl/lib/libcurl.lib"
        INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/libs/curl/include"
        )

add_subdirectory(cblox)