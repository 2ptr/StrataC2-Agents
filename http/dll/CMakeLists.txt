cmake_minimum_required(VERSION 3.31)
project(dll)

set(CMAKE_CXX_STANDARD 20)

add_library(dll SHARED
        library.cpp
        conf/Callbacks.cpp
        commands/CommandHelper.cpp
        commands/Filesystem.cpp
        commands/Execution.cpp
        commands/Management.cpp
)
target_include_directories(dll PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/conf
        ${CMAKE_CURRENT_SOURCE_DIR}/lib
        ${CMAKE_CURRENT_SOURCE_DIR}/commands
)
target_link_libraries(dll PRIVATE winhttp wininet iphlpapi ws2_32 psapi)

set_target_properties(dll PROPERTIES
        OUTPUT_NAME "MyLibrary"
        PREFIX ""  # Removes the 'lib' prefix on Unix systems
)