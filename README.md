# Codebreakers
This is a program that allows you to encrypt and decrypt messages into text files. It will consist of being able to encode a message and how to decode it. I will be using C++ to create this.

## How To Compile & Test
```bash
1. g++ main.cpp -o cipher
2. Change input file to message you want to encode/decode
3. Enter Commands.
```

### Commands
```bash
1. ./cipher input.txt output.txt <upper/lower/reverse>
2. ./program <in> <out> cipher <shift> <encode/decode>
3. ./program <in> <out> rot <shift>
4. ./program <in> <out> vigenere <key> <encode/decode>
```
Example:
```bash
g++ main.cpp -o cipher
INPUT FILE: "Hello!"
./program input.txt output.txt cipher 3 encode
OUTPUT FILE: "khoor!"
```
