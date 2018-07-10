cmake_minimum_required(VERSION 3.10)
project(SaFStproj C)

add_definitions(-D_FILE_OFFSET_BITS=64)
set(CMAKE_C_STANDARD 11)
set(FUSE_USE_VERSION 30)
add_executable(SaFStproj
        fs.c
        fs.h
        main.c db.c db.h)
