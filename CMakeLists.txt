cmake_minimum_required(VERSION 3.24)
project(2023S2_ECELECAR C)

set(CMAKE_C_STANDARD 23)

add_executable(2023S2_ECELECAR
        main.c
        header_gen.h

        TEMPLATE/main.c
        TEMPLATE/header_gen.h
)

