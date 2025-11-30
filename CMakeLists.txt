cmake_minimum_required(VERSION 3.26)

project(Shas_Shell C)

set(CMAKE_C_STANDARD 11)

add_executable(Shas_Shell
        exec.c
        functions.h
        tokeniser.c
        parser.c
        command.h
)