cmake_minimum_required(VERSION 3.25)
project(2048_Program)

set(CMAKE_CXX_STANDARD 23)

add_executable(2048_Program main.cpp Board.h RANDOM_MT_H.h)
