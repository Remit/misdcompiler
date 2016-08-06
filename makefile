all: misdcompiler.exe

misdcompiler.exe: main.o
	cd parser && make
	g++ -g -o misdcompiler main.o parser/bison-misdcompiler.o parser/flex-misdcompiler.o
	
main.o:
	g++ -c -g main.cpp
	
clean:
	cd parser && make clean
	rm main.o misdcompiler.exe