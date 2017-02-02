CPP_FILES := $(wildcard *.cpp)
OBJ_FILES := $(notdir $(CPP_FILES:.cpp=.o))
CXXFLAGS := `/bin/llvm-config --cxxflags`

all: $(OBJ_FILES)

%.o: %.cpp ../include/%.h
	g++ $(CXXFLAGS) -c -o $@ $< -std=c++11

.SILENT : clean
.PHONY : clean	
clean:
	-rm -f $(OBJ_FILES)
