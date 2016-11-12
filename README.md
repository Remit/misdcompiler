# misdcompiler
A native compiler for MISD computer architecture.

## Parser
The compiler can be constructed using makefile in the root directory.
Separate compiler parts (lexical analyser, syntactical analyser, etc.) can be translated and compiled separatle. Instructions can be found below.

In order to add new syntactical rules and new tokens, you must have flex and bison installed.
Commands for translation and compilation of misdcompiler.ypp:
- ordinary translation (no tokens changed/added): bison misdcompiler.ypp
- translation with tokens changed/added: bison -d misdcompiler.ypp (generated header is used in .lex file)
- compilation

Commands for translation and compilation of misdcompiler.lex:
- translation: flex misdcompiler.lex
- compilation using tokens defs and other defs by bison: g++ -o misdlex flex-misdcompiler.cpp misdcompiler.tab.hpp -lfl

## Development ideas
- graphs visualisation using JS (there are special libraries): generating JS page and opening it with browser (use flag to specify whether we need to generate those visualisations or not
- libraries for different applications (e.g. graph databases)

## Visualisation in form of graphs
- We use free open-source Cytospace library to visualise program graphs
- Graph visualisations of programs are stored in the folder "Visualisation"
- Visualisation is provided by using "-v" when compiling
