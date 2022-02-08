cmake_minimum_required(VERSION 3.20)
project(week12 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(week12
        week12_1/week12_01.c
        week12_2/week12_02.c)
