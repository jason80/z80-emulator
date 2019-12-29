cmake_minimum_required(VERSION 3.5)

file(GLOB cp_emu_sources "*.c")
file(GLOB core_sources "${z80emu_SOURCE_DIR}/core/*.c")

include_directories(${z80emu_SOURCE_DIR}/core)

add_executable(cp-emu ${cp_emu_sources} ${core_sources})
target_link_libraries(cp-emu ncurses)
