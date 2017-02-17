# disccompiler
A native compiler for Discrete mathematical Instructions Set (DISC) computer architecture.

## On DISC computer architecture
DISC computer architecture is a clear example of MISD class according to Flynn’s classification – the single data stream consisting both of data structures and simple variables is processed simultaneously by two cores.

The first core, which is represented by a standard CPU, conducts arithmetical and logical operations on the contents of data structures and on simple variables. The second core, namely structures processing unit (SPU) “Leonhard”, which is another project of our Research group, conducts operations on data structures: insertion and deletion of an element of data structure, intersection, union and subtraction of structures, etc. The operations supported on the level of hardware of the second core form a complete basis of dicscrete mathematics. Both cores have separate memory for respective types of data processed and memory for programs that are executed by these cores. At the program execution time, the communication between cores is conducted using buffers. Currently, the DISC computer’s prototype is implemented on a FPGA board.

The paper on the DISC computer architecture as an example of MISD class could be found here: https://scholarspace.manoa.hawaii.edu/handle/10125/41272/

## Prerequisites
In order to compile the compiler you should have the following software:
- Linux (e.g. https://www.archlinux.org/)
- GCC ver. >= 6.2.1 (https://gcc.gnu.org/)
- GNU flex (https://github.com/westes/flex)
- GNU bison (https://www.gnu.org/software/bison/), some older versions may require **-lfl** option
- CLANG /w LLVM ver. >= 3.9 (http://clang.llvm.org/)
- Web Browser with support for JavaScript

## Compiler Compilation
The compiler can be compiled using makefile in the root directory.
In order to compile the compiler, open the Terminal, change to the source code directory and run `make` command.
After some time, you will see the **disccompiler** binary in the same directory.

## Usage
The compilation command format is as follows:

```disccompiler [FILE WITH SOURCE CODE, .mcc FORMAT] [DESTINATION BINARY, .out FORMAT] [[-v ias]] [[-ast asf [[OUTPUT FILE FOR ASTs, .txt FORMAT]] ]] [[-asm asf [[OUTPUT FILE FOR ASM IRs, .txt FORMAT]] ]]```

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

As a result of the compiler's usage you will receive the following artifacts:
- [*mandatory*] a binary to run on the machine with a driver and an on-board FPGA SPU connected through PCI
- [*not mandatory*] graph representations of initial and decomposed algorithms in the form of corresponding HTML files in *Visualisation* directory of the compiler using JavaScript files from the same directory
- [*not mandatory*] a file with text representations of AST for arithmetic-logic instructions stream and of AST for structure processing instructions stream
- [*not mandatory*] a file with assembler commands for arithmetic-logic instructions and for structure processing instructions stream

## Development ideas
- Libraries for specific applications and platforms that may proliferate from the hardware-supported operations on data structures (if interested, contact us: v.e.podolskiy@gmail.com)
- Support for uploading the structured data into SPU structures memory
- Extensions to existing compilers and technologies to support MISD architecture
- Documentation (esp. on language supported by the compiler)