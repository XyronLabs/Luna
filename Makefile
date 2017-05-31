BIN := bin
SRC := src

EXE := luna
MAIN := main.cpp

CXXFLAGS := -std=c++14

all: $(BIN)/$(EXE)

$(BIN)/$(EXE): $(SRC)/$(MAIN)
	$(CXX) $(CXXFLAGS) $< -o $@ -llua -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system

clean:
	-@rm $(BIN)/$(EXE)

run: all
	./$(BIN)/$(EXE)