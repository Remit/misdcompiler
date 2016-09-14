all: bison-misdcompiler.o flex-misdcompiler.o

bison-misdcompiler.o: bison-misdcompiler.cpp
	g++ -c bison-misdcompiler.cpp -o bison-misdcompiler.o

flex-misdcompiler.o: flex-misdcompiler.cpp
	g++ -c flex-misdcompiler.cpp -o flex-misdcompiler.o

bison-misdcompiler.cpp: misdcompiler.ypp
	bison -d misdcompiler.ypp
	
flex-misdcompiler.cpp: misdcompiler.lex
	flex misdcompiler.lex
	
clean:
	-rm flex-misdcompiler.o bison-misdcompiler.o \
		 flex-misdcompiler.cpp bison-misdcompiler.cpp \
		 ../include/bison-misdcompiler.h.gch ../include/flex-misdcompiler.h.gch \
		 ../include/bison-misdcompiler.h ../include/flex-misdcompiler.h