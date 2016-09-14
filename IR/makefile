CPP_FILES := $(wildcard *.cpp)
OBJ_FILES := $(notdir $(CPP_FILES:.cpp=.o))

all: $(OBJ_FILES)

%.o: %.cpp ../include/%.h
	g++ -c -o $@ $<
	
clean:
	-rm $(OBJ_FILES)
