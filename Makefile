# Directories #
BIN 	:= bin
SRC 	:= src
INCLUDE := include
OBJ 	:= obj
OUT 	:= out

# Configurations #
DEBUG   := debug
RELEASE := release
CONFIG  := release

EXE  := luna
MAIN := main.cpp

# Files needed for compiling #
sources           := $(wildcard $(SRC)/*.cpp)
objects-$(CONFIG) := $(patsubst $(SRC)/%.cpp, $(OBJ)/%-$(CONFIG).o, $(sources))

# Libraries #
libraries := -llua5.3 -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system

# Compiler options for each configuration #
CXXFLAGS            := -std=c++14 -Wall
CXXFLAGS_$(RELEASE) := -O3
CXXFLAGS_$(DEBUG)   := -DLUNA_DEBUG


all: $(CONFIG)

#-- Shortcuts --#
r:
	$(MAKE) -j4 CONFIG=release
d:
	$(MAKE) -j4 CONFIG=debug


#-------------------------------------------------------------------#
#                           Configuration                           #
#-------------------------------------------------------------------#
$(CONFIG): $(objects-$(CONFIG)) DIRS
	$(CXX) $(objects-$(CONFIG)) -o $(BIN)/$(EXE)-$@ $(libraries)

$(OBJ)/%-$(CONFIG).o: $(SRC)/%.cpp DIRS
	$(CXX) $(CXXFLAGS) $(CXXFLAGS_$(CONFIG)) $< -c -o $@ -I$(INCLUDE)


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