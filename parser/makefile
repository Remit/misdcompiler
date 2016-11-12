all: bison-misdcompiler.o flex-misdcompiler.o

bison-misdcompiler.o: bison-misdcompiler.cpp
	g++ -c bison-misdcompiler.cpp -o bison-misdcompiler.o -std=c++11

flex-misdcompiler.o: flex-misdcompiler.cpp
	g++ -c flex-misdcompiler.cpp -o flex-misdcompiler.o -std=c++11

bison-misdcompiler.cpp: misdcompiler.ypp
	bison -d misdcompiler.ypp
	
flex-misdcompiler.cpp: misdcompiler.lex
	flex misdcompiler.lex

.SILENT : clean
.PHONY : clean	
clean:
	-rm -f flex-misdcompiler.o bison-misdcompiler.o \
		 flex-misdcompiler.cpp bison-misdcompiler.cpp \
		 ../include/bison-misdcompiler.h.gch ../include/flex-misdcompiler.h.gch \
		 ../include/bison-misdcompiler.h ../include/flex-misdcompiler.h
