cmake_minimum_required(VERSION 3.14)

set(INCLUDE_DIR src/include)
set(CMAKE_EXPORT_COMPILE_COMANDS on)
set(CMAKE_CXX_STANDARD 17)
project(2BCompiler CXX)

add_executable(
    2bc
    src/Ayanami.cpp
)