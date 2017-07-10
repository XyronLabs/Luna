BIN := bin
SRC := src
INCLUDE := include

EXE := luna
MAIN := main.cpp

sources := $(wildcard src/*.cpp)
libs := -llua5.3 -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system

CXXFLAGS := -std=c++14

all: $(BIN)/$(EXE)

$(BIN)/$(EXE): $(sources) $(BIN)
	$(CXX) $(CXXFLAGS) $(sources) -o $@ -I$(INCLUDE) $(libs)

$(BIN):
	mkdir $(BIN)

clean:
	-@rm $(BIN)/$(EXE)

run: all
	./$(BIN)/$(EXE)

install: all
	cp $(BIN)/$(EXE) /usr/local/bin/