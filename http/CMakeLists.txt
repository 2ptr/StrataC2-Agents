cmake_minimum_required(VERSION 3.31)
project(strata-exe)

set(CMAKE_CXX_STANDARD 20)

add_executable(strata-exe main.cpp
        conf/Callbacks.h
        conf/Config.h
        conf/Callbacks.cpp
        commands/CommandHelper.cpp
        commands/CommandHelper.h
        commands/Filesystem.cpp
        commands/Execution.cpp
        commands/Management.cpp
)
if (WIN32)
    set_target_properties(strata-exe PROPERTIES LINK_FLAGS "-Wl,-subsystem,windows" )
endif()

target_link_libraries(strata-exe PRIVATE winhttp wininet iphlpapi ws2_32 )
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -static -static-libgcc -static-libstdc++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static -static-libgcc -static-libstdc++")

project(strata-dll)

set(CMAKE_CXX_STANDARD 20)

add_library(strata-dll SHARED
        library.cpp
        conf/Callbacks.cpp
        commands/CommandHelper.cpp
        commands/Filesystem.cpp
        commands/Execution.cpp
        commands/Management.cpp
)
target_include_directories(strata-dll PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/conf
        ${CMAKE_CURRENT_SOURCE_DIR}/lib
        ${CMAKE_CURRENT_SOURCE_DIR}/commands
)
target_link_libraries(strata-dll PRIVATE winhttp wininet iphlpapi ws2_32 psapi)

set_target_properties(strata-dll PROPERTIES
        OUTPUT_NAME "strata-dll"
        PREFIX ""  # Removes the 'lib' prefix on Unix systems
)
