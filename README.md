# misdcompiler
A native compiler for MISD computer architecture

## Parser
In order to add new syntactical rules and new tokens, you must have flex and bison installed.
Commands for translation and compilation of misdcompiler.ypp:
- ordinary translation (no tokens changed/added): bison misdcompiler.ypp
- translation with tokens changed/added: bison -d misdcompiler.ypp (generated hpp is used in .lex file)
- compilation
Commands for translation and compilation of misdcompiler.lex:
- translation: flex misdcompiler.lex
- compilation using tokens defs and other defs by bison: g++ -o misdlex flex-misdcompiler.cpp misdcompiler.tab.hpp -lfl
