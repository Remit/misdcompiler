The main goal of Intermediate Representation (IR) in the compiler is to create a program representation that can be easily separated into two parts:
- program graph of arithmetical and logical operations (CPU part);
- program graph of operations on data structures (SPU part).

The IR is divided into these two graphs on the parallelization stage of processing.
Each IR node includes a subsequent part of program AST in order to reconstruct the AST's after parallelization stage is finished with its IR processing tasks.
