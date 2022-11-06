cmake_minimum_required(VERSION 3.14)

set(INCLUDE_DIR src/include)
set(CMAKE_EXPORT_COMPILE_COMANDS on)
project(2BCompiler C)

add_executable(
    2bc
    src/Ayanami.c
)