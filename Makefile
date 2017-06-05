BIN := bin
SRC := src
INCLUDE := include

EXE := luna
MAIN := main.cpp

sources := $(wildcard src/*.cpp)
libs := -llua -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system

CXXFLAGS := -std=c++14

all: $(BIN)/$(EXE)

$(BIN)/$(EXE): $(sources)
	$(CXX) $(CXXFLAGS) $(sources) -o $@ -I$(INCLUDE) $(libs)

clean:
	-@rm $(BIN)/$(EXE)

run: all
	./$(BIN)/$(EXE)