cmake_minimum_required(VERSION 3.15)
project(sp3lab1 C)

set(CMAKE_C_STANDARD 99)

add_executable(SP3 main.c lib/alloc.c)