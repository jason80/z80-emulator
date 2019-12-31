cmake_minimum_required(VERSION 3.5)

file(GLOB dis_sources "disassembler.c" "dis_tables.c")

add_executable(dis-test test.c ${dis_sources})
