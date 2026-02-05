cmake_minimum_required(VERSION 3.16)
project(c_dllist C)

set(CMAKE_C_STANDARD 11)

add_executable(c_dllist
        main.c
        dllist.c)
