cmake_minimum_required(VERSION 3.15)
project(srf C)

set(CMAKE_C_STANDARD 11)

include_directories(. /usr/local/src/pg11/src/include /usr/local/src/pg11/src/backend)

add_executable(srf
        srf.c)
