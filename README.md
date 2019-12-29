# z80-emulator

- Requirements:
gcc compiler, CMake.
CUnit1 test unit lib.

- Compile:
```sh
mkdir bin
cd bin
cmake ..
```
- Run:

```sh
./test/z80test
```
- Test Assembly
Install z80asm assembler package.

Example:
```sh
z80asm test/asm/djnz.asm -o test/asm/djnz.bin
```
