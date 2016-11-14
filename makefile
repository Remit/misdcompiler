CPP_FILES_IR := $(wildcard IR/*.cpp)
CPP_FILES_AST := $(wildcard AST/*.cpp)
OBJ_FILES_IR := $(patsubst %.cpp,%.o,$(CPP_FILES_IR))
OBJ_FILES_AST := $(patsubst %.cpp,%.o,$(AST_FILES_IR))
OBJ_FILES_PARSER := parser/bison-misdcompiler.o parser/flex-misdcompiler.o
GCH_FILES := $(patsubst %.cpp,%.h.gch,$(CPP_FILES_IR))

TMP_FILES_ROOT := $(wildcard *~)
TMP_FILES_IR := $(wildcard IR/*~)
TMP_FILES_INCLUDE := $(wildcard include/*~)
TMP_FILES_PARSER := $(wildcard parser/*~)
TMP_FILES_AST := $(wildcard AST/*~)
TMP_FILES_EXAMPLES := $(wildcard examples/*~)

all: misdcompiler.exe

misdcompiler.exe: main.o
	cd IR && make
	cd AST && make
	cd parser && make
	g++ -g -o misdcompiler main.o $(OBJ_FILES_IR) $(OBJ_FILES_PARSER) $(OBJ_FILES_AST) -std=c++11

main.o:
	g++ -c -g main.cpp

.SILENT : clean
.PHONY : clean
clean:
	cd Visualisation && make clean
	cd parser && make clean
	cd AST && make clean
	cd IR && make clean
	-rm -f main.o misdcompiler
	-rm -rf $(TMP_FILES_ROOT) $(TMP_FILES_IR) $(TMP_FILES_INCLUDE) $(TMP_FILES_PARSER) $(TMP_FILES_AST) $(TMP_FILES_EXAMPLES)

