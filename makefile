OBJ_FILES := $(wildcard IR/*.o)
HDR_FILES := $(wildcard include/*.h)

all: misdcompiler.exe

misdcompiler.exe: main.o
	cd parser && make
	cd IR && make
	g++ -g -o misdcompiler include/BaseAST.h include/build.h include/CommonTypesAndConstants.h include/IRDataNode.h include/IRGraph.h include/IRNode.h include/IROperationNode.h include/StructuresTable.h include/VariablesTable.h main.o parser/bison-misdcompiler.o parser/flex-misdcompiler.o $(OBJ_FILES)
	
main.o:
	g++ -c -g main.cpp
	
clean:
	cd parser && make clean
	cd IR && make clean
	rm main.o misdcompiler.exe