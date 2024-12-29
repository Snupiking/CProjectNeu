cmake_minimum_required(VERSION 3.28.3)
project(CProjektNeu C)

set(CMAKE_C_STANDARD 11)

# Liste der Quellcodedateien (.c)
add_executable(CProjektNeu main.c
        Input.c
        outputDir.c
)
