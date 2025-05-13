cmake_minimum_required(VERSION 3.31)
project(exe)

set(CMAKE_CXX_STANDARD 20)

add_executable(exe main.cpp
        conf/Callbacks.h
        conf/Config.h
        conf/Callbacks.cpp
        commands/CommandHelper.cpp
        commands/CommandHelper.h
        commands/Filesystem.cpp
        commands/Execution.cpp
)

target_link_libraries(exe PRIVATE winhttp wininet iphlpapi ws2_32 )