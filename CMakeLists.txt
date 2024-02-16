cmake_minimum_required(VERSION 3.26)
project(HTTPinC C)

set(CMAKE_C_STANDARD 17)

add_executable(HTTPinC main.c
        Server.c
        Server.h)
