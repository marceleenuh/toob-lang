cmake_minimum_required(VERSION 3.14)

set(INCLUDE_DIR src/include)
set(CMAKE_EXPORT_COMPILE_COMANDS on)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_FLAGS "-O5")
project(2BCompiler C)

add_executable(
    2bc
    src/Ayanami.c
    src/parser.c
    src/error.c
    src/fileIO.c
    src/Environment.c
)
target_include_directories(2bc PRIVATE ${INCLUDE_DIR})