cmake_minimum_required(VERSION 3.10)
project(SaFSt)
set(CMAKE_C_STANDARD 11)
link_directories(/usr/local/lib/x86_64-linux-gnu)  # Where fuse is located by default, if it is not there it needs to be close to that.
add_executable(SaFSt
        fs.c
        fs.h
        main.c)
target_link_libraries(SaFSt fuse3) # fuse2 is outdated and ubuntu usually has fuse2
add_definitions(-D_FILE_OFFSET_BITS=64)