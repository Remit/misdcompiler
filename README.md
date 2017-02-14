# misdcompiler
A native compiler for MISD computer architecture.

## Prerequisites
In order to compile the MISD compiler you should have the following software:
- Linux (e.g. https://www.archlinux.org/)
- GCC ver. >= 6.2.1 (https://gcc.gnu.org/)
- GNU flex (https://github.com/westes/flex)
- GNU bison (https://www.gnu.org/software/bison/), some older versions may require **-lfl** option
- CLANG /w LLVM ver. >= 3.9 (http://clang.llvm.org/)
- Web Browser with support for JavaScript

## Compiler Compilation
The compiler can be compiled using makefile in the root directory.
In order to compile the MISD compiler, open the Terminal, change to the source code directory and run `make` command.
After some time, you will see the **misdcompiler** binary in the same directory.

## Usage
The compilation command format is as follows:
`misdcompiler [FILE WITH SOURCE CODE, .mcc FORMAT] [DESTINATION BINARY, .out FORMAT] [[-v ias]] [[-ast asf [[OUTPUT FILE FOR ASTs, .txt FORMAT]] ]] [[-asm asf [[OUTPUT FILE FOR ASM IRs, .txt FORMAT]] ]]`
where
`[...]` - mandatory parts of command,
`[[...]]` - non-mandatory parts of command,
`-v` - IR graphs visualization option with parameters:
- `i` - visualize graph IR for the initial program (`-` - no vizualization for initial IR)
- `a` - visualize graph IR for the arithmetic-logic part of program (`-` - no vizualization for arithmetic-logic IR)
- `s` - visualize graph IR for the structures processing part of program (`-` - no vizualization for structures processing IR),
`-ast` - AST print option with parameters:
- `a` - print AST for the arithmetic-logic part of program (`-` - no AST print for the arithmetic-logic part of program)
- `s` - print AST for the structures processing part of program (`-` - no AST print for the structures processing part part of program)
- `f` - print ASTs to the following file (`-` - print to standard output),
`-asm` - assembler IR print option with parameters:
- `a` - print asm IR for the arithmetic-logic part of program, provided by LLVM (`-` - no asm IR print for the arithmetic-logic part of program)
- `s` - print asm IR for the structures processing part of program (`-` - no asm IR print for the structures processing part part of program)
- `f` - print asm IRs to the following file (`-` - print to standard output).

## Development ideas
- Libraries for specific solutions
- Support for uploading the structured data into SPU structures memory
- Documentation (esp. on language)