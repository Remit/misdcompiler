CPP_FILES_IR := $(wildcard IR/*.cpp)
OBJ_FILES_IR := $(patsubst %.cpp,%.o,$(CPP_FILES_IR))
OBJ_FILES_PARSER := parser/bison-misdcompiler.o parser/flex-misdcompiler.o
GCH_FILES := $(patsubst %.cpp,%.h.gch,$(CPP_FILES_IR))

all: misdcompiler.exe

misdcompiler.exe: main.o
	cd IR && make
	cd parser && make
	g++ -g -o misdcompiler main.o $(OBJ_FILES_IR) $(OBJ_FILES_PARSER) -lfl
	
main.o:
	g++ -c -g main.cpp
	
clean:
	cd parser && make clean
	cd IR && make clean
	-rm main.o misdcompiler
	-rm $(GCH_FILES)