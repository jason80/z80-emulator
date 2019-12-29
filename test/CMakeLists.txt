cmake_minimum_required(VERSION 3.10)

file (GLOB test_sources "*.c")
file (GLOB core_sources "${z80emu_SOURCE_DIR}/core/*.c")

include_directories(${z80emu_SOURCE_DIR/core})

add_executable(z80test ${test_sources} ${core_sources})
target_link_libraries(z80test cunit)
