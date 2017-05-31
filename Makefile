BIN := bin
SRC := src

all: $(BIN)/main

$(BIN)/main: $(SRC)/main.cpp
	$(CXX) $< -o $@ -llua -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system