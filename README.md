# z80-emulator

- Requirements:
gcc compiler, CMake.
CUnit1 test unit lib.

- Compile:
```sh
mkdir bin
cd bin
cmake ..
make
```
- Run tests:
```sh
./test/z80test
```

- Run emulator
```sh
./cp-emu/cp-emu
```

- Test Assembly
Install z80asm assembler package.

Example:
```sh
z80asm test/asm/djnz.asm -o test/asm/djnz.bin
```
