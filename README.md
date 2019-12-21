# z80-emulator

- Requirements:
gcc compiler, make.
CUnit1 test unit lib.

- Compile:
```sh
make
```
- Run:

```sh
./build/bin/test
```
- Test Assembly
Install z80asm assembler package.

Example:
```sh
z80asm test/asm/djnz.asm -o test/asm/djnz.bin
```
