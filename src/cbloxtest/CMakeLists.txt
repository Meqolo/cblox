project(cbloxtest)

add_executable(cbloxtest
        src/ctest.cpp)

target_link_libraries(cbloxtest
        cblox
        -static-libgcc -static-libstdc++ -Wl,-Bstatic -lstdc++ -lpthread -Wl,-Bdynamic)