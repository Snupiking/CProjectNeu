cmake_minimum_required(VERSION 3.30)
project(CProjektNeu C)

set(CMAKE_C_STANDARD 11)

# Liste der Quellcodedateien (.c)
add_executable(CProjektNeu main.c
        Input.c
        outputDir.c
        list.c
)
