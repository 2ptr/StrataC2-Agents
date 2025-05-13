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
if (WIN32)
    set_target_properties(exe PROPERTIES
            LINK_FLAGS "-Wl,-subsystem,windows"
    )
endif()

target_link_libraries(exe PRIVATE winhttp wininet iphlpapi ws2_32 )
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -static -static-libgcc -static-libstdc++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static -static-libgcc -static-libstdc++")