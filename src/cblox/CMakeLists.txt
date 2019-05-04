project(cblox)

add_library(cblox STATIC
        src/group.cpp
        src/http.cpp
        src/other.cpp
        src/user.cpp)

target_include_directories(cblox PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE src)

include_directories( ${CURL_INCLUDE_DIRS} )
link_directories( ${CURL_LIBRARIES})

target_compile_features(cblox
        PUBLIC cxx_auto_type
        PRIVATE cxx_variadic_templates)

target_link_libraries(cblox
        curl
        wldap32
        ws2_32
        nlohmann_json)

install(TARGETS cblox EXPORT CbloxConfig
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})  # This is for Windows
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT CbloxConfig DESTINATION cmake)
export(TARGETS cblox FILE CbloxConfig.cmake)