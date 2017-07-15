# Directories #
BIN 	:= bin
SRC 	:= src
INCLUDE := include
OBJ 	:= obj
OUT 	:= out

EXE	 := luna
MAIN := main.cpp

# Files needed for compiling #
sources   := $(wildcard src/*.cpp)
objects   := $(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(sources))
objects-d := $(patsubst %.o, %-d.o, $(objects))

# Libraries #
libs := -llua5.3 -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system

# Compiler options for each configuration #
CXXFLAGS		 := -std=c++14 -Wall
CXXFLAGS_RELEASE := -O3
CXXFLAGS_DEBUG   := -DLUNA_DEBUG


all: release


#-------------------------------------------------------------------#
#                       Release configuration                       #
#-------------------------------------------------------------------#
release: $(objects) DIRS
	$(CXX) $(objects) -o $(BIN)/$(EXE)-$@ $(libs)

$(OBJ)/%.o: $(SRC)/%.cpp
	$(CXX) $(CXXFLAGS) $(CXXFLAGS_RELEASE) $< -c -o $@ -I$(INCLUDE)

#-------------------------------------------------------------------#
#                        Debug configuration                        #
#-------------------------------------------------------------------#
debug: $(objects-d) DIRS
	$(CXX) $(objects-d) -o $(BIN)/$(EXE)-$@ $(libs)

$(OBJ)/%-d.o: $(SRC)/%.cpp
	$(CXX) $(CXXFLAGS) $(CXXFLAGS_DEBUG) $< -c -o $@ -I$(INCLUDE)


# Directories #
DIRS:
	mkdir -p $(BIN) $(OBJ) $(OUT)

clean:
	-rm -f $(BIN)/* $(OBJ)/* $(OUT)/*
	-rm -rf deb

run: debug
	./$(BIN)/$(EXE)-debug


install:
	-rm /usr/local/bin/$(EXE)
	cp $(BIN)/$(EXE)-release /usr/local/bin/$(EXE)
	-mkdir /usr/local/luna
	-cp -rf lua/ /usr/local/luna/
	-cp -rf res/ /usr/local/luna/


deb: release DIRS
	mkdir -p deb/usr/local/bin/ deb/usr/local/luna/ deb/DEBIAN/
	cp $(BIN)/$(EXE)-release deb/usr/local/bin/$(EXE)
	cp control deb/DEBIAN/
	cp -rf lua/ deb/usr/local/luna/
	cp -rf res/ deb/usr/local/luna/
	dpkg-deb -b deb out/luna.deb
	rm -rf deb