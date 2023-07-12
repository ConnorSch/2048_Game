cmake_minimum_required(VERSION 3.25)
project(2048_Program)

set(CMAKE_CXX_STANDARD 20)

add_library(SQLite
        SQLite/sqlite3.c
        SQLite/sqlite3.h
        SQLite/shell.c
        SQLite/sqlite3ext.h)

target_link_libraries(SQLite sqlite3)

add_executable(2048_Program main.cpp Board.h RANDOM_MT_H.h Board.cpp)

target_link_libraries(2048_Program SQLite)
