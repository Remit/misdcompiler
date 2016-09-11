all: bison-misdcompiler.o flex-misdcompiler.o

bison-misdcompiler.o: bison-misdcompiler.cpp
	g++ -c -g ../include/bison-misdcompiler.h bison-misdcompiler.cpp
	
bison-misdcompiler.cpp:
	bison -d misdcompiler.ypp
	
flex-misdcompiler.o: bison-misdcompiler.o flex-misdcompiler.cpp	
	g++ -c -g ../include/bison-misdcompiler.h flex-misdcompiler.cpp

flex-misdcompiler.cpp:
	flex misdcompiler.lex
	
clean:
	rm flex-misdcompiler.o bison-misdcompiler.o \
		 flex-misdcompiler.cpp bison-misdcompiler.cpp
		 ../include/bison-misdcompiler.h.gch ../include/flex-misdcompiler.h.gch \
		 ../include/bison-misdcompiler.h ../include/flex-misdcompiler.h