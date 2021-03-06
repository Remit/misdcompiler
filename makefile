CPP_FILES_IR := $(wildcard IR/*.cpp)
CPP_FILES_AST := $(wildcard AST/*.cpp)
CPP_FILES_HELPERS := $(wildcard Helpers/*.cpp)
OBJ_FILES_IR := $(patsubst %.cpp,%.o,$(CPP_FILES_IR))
OBJ_FILES_AST := $(patsubst %.cpp,%.o,$(CPP_FILES_AST))
OBJ_FILES_HELPERS := $(patsubst %.cpp,%.o,$(CPP_FILES_HELPERS))
OBJ_FILES_PARSER := parser/bison-misdcompiler.o parser/flex-misdcompiler.o
GCH_FILES := $(patsubst %.cpp,%.h.gch,$(CPP_FILES_IR))

TMP_FILES_ROOT := $(wildcard *~)
TMP_FILES_IR := $(wildcard IR/*~)
TMP_FILES_INCLUDE := $(wildcard include/*~)
TMP_FILES_PARSER := $(wildcard parser/*~)
TMP_FILES_AST := $(wildcard AST/*~)
TMP_FILES_EXAMPLES := $(wildcard examples/*~)

LLVMLIBS = `/bin/llvm-config --libs`
LDFLAGS += `/bin/llvm-config --ldflags`

all: disccompiler.exe

disccompiler.exe: main.o Passes.o
	cd Helpers && make
	cd AST && make
	cd IR && make
	cd parser && make
	g++ $(LDFLAGS) -g -o disccompiler main.o Passes.o $(OBJ_FILES_HELPERS) $(OBJ_FILES_IR) $(OBJ_FILES_PARSER) $(OBJ_FILES_AST) $(LLVMLIBS) -std=c++11

Passes.o: Passes.cpp
	g++ -c -g Passes.cpp
	
main.o: main.cpp
	g++ -c -g main.cpp

.SILENT : clean
.PHONY : clean
clean:
	cd Visualisation && make clean
	cd Helpers && make clean
	cd parser && make clean
	cd AST && make clean
	cd IR && make clean
	-rm -f main.o Passes.o disccompiler
	-rm -rf $(TMP_FILES_ROOT) $(TMP_FILES_IR) $(TMP_FILES_INCLUDE) $(TMP_FILES_PARSER) $(TMP_FILES_AST) $(TMP_FILES_EXAMPLES)

