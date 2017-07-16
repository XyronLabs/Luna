# Directories #
BIN 	:= bin
SRC 	:= src
INCLUDE := include
OBJ 	:= obj
OUT 	:= out

# Configurations #
DEBUG   := debug
RELEASE := release

EXE  := luna
MAIN := main.cpp

# Files needed for compiling #
sources   := $(wildcard $(SRC)/*.cpp)
objects   := $(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(sources))
objects-d := $(patsubst %.o, %-$(DEBUG).o, $(objects))

# Libraries #
libraries := -llua5.3 -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system

# Compiler options for each configuration #
CXXFLAGS         := -std=c++14 -Wall
CXXFLAGS_RELEASE := -O3
CXXFLAGS_DEBUG   := -DLUNA_DEBUG


all: $(RELEASE)


#-------------------------------------------------------------------#
#                       Release configuration                       #
#-------------------------------------------------------------------#
$(RELEASE): $(objects) DIRS
	$(CXX) $(objects) -o $(BIN)/$(EXE)-$@ $(libraries)

$(OBJ)/%.o: $(SRC)/%.cpp DIRS
	$(CXX) $(CXXFLAGS) $(CXXFLAGS_RELEASE) $< -c -o $@ -I$(INCLUDE)

#-------------------------------------------------------------------#
#                        Debug configuration                        #
#-------------------------------------------------------------------#
$(DEBUG): $(objects-d) DIRS
	$(CXX) $(objects-d) -o $(BIN)/$(EXE)-$@ $(libraries)

$(OBJ)/%-$(DEBUG).o: $(SRC)/%.cpp DIRS
	$(CXX) $(CXXFLAGS) $(CXXFLAGS_DEBUG) $< -c -o $@ -I$(INCLUDE)


# Directories #
DIRS:
	mkdir -p $(BIN) $(OBJ) $(OUT)

clean:
	-rm -f $(BIN)/* $(OBJ)/* $(OUT)/*
	-rm -rf deb

run: $(DEBUG)
	./$(BIN)/$(EXE)-$(DEBUG)


install:
	-rm /usr/local/bin/$(EXE)
	cp $(BIN)/$(EXE)-$(RELEASE) /usr/local/bin/$(EXE)
	-mkdir /usr/local/luna
	-cp -rf lua/ /usr/local/luna/
	-cp -rf res/ /usr/local/luna/


deb: $(RELEASE) DIRS
	mkdir -p deb/usr/local/bin/ deb/usr/local/luna/ deb/DEBIAN/
	cp $(BIN)/$(EXE)-$(RELEASE) deb/usr/local/bin/$(EXE)
	cp control deb/DEBIAN/
	cp -rf lua/ deb/usr/local/luna/
	cp -rf res/ deb/usr/local/luna/
	dpkg-deb -b deb out/luna.deb
	rm -rf deb