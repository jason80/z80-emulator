cmake_minimum_required(VERSION 3.5)
project(z80emu)

set(CMAKE_C_FLAGS "-Wall --pedantic -g")

add_subdirectory(core)
add_subdirectory(test)
add_subdirectory(cp-emu)
add_subdirectory(disassembler)
