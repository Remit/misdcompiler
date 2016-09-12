OBJ_FILES_IR := $(wildcard IR/*.o)
OBJ_FILES_PARSER := $(wildcard parser/*.o)
HDR_FILES := $(wildcard include/*.h)

all: misdcompiler.exe

misdcompiler.exe: main.o
	cd parser && make
	cd IR && make
	g++ -g -o misdcompiler main.o $(OBJ_FILES_PARSER) $(OBJ_FILES)
	
main.o:
	g++ -c -g main.cpp
	
clean:
	cd parser && make clean
	cd IR && make clean
	rm main.o misdcompiler.exe