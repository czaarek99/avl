cmake_minimum_required(VERSION 3.14)
project(avl C)

set(CMAKE_C_STANDARD 11)

add_executable(avl src/main.c src/avl.h src/avl.c)