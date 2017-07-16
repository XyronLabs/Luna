# Directories #
BIN 	:= bin
DEB     := deb
INCLUDE := include
OBJ 	:= obj
OUT 	:= out
SRC 	:= src


# Configurations #
RELEASE := release
DEBUG   := debug

# Default configuration #
CONFIG  := release

EXE  := luna
MAIN := main.cpp


# Installation paths #
BASE_PATH := usr/local
INSTALL_PATH := $(BASE_PATH)/$(EXE)
EXE_PATH := $(BASE_PATH)/bin/$(EXE)


# Files needed for compiling #
sources           := $(wildcard $(SRC)/*.cpp)
objects-$(CONFIG) := $(patsubst $(SRC)/%.cpp, $(OBJ)/%-$(CONFIG).o, $(sources))

# Libraries #
libraries := -llua5.3 -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system

# Compiler options for each configuration #
CXXFLAGS            := -std=c++14 -Wall
CXXFLAGS_$(RELEASE) := -O3
CXXFLAGS_$(DEBUG)   := -DLUNA_DEBUG



#----------------------------  Targets  ----------------------------#

all: $(CONFIG)

#-- Shortcuts --#
r:
	$(MAKE) -j4 CONFIG=release
d:
	$(MAKE) -j4 CONFIG=debug
o:
	$(MAKE) -j4 deb


#-------------------------------------------------------------------#
#                           Configuration                           #
#-------------------------------------------------------------------#
$(CONFIG): $(objects-$(CONFIG)) DIRS
	$(CXX) $(objects-$(CONFIG)) -o $(BIN)/$(EXE)-$@ $(libraries)

$(OBJ)/%-$(CONFIG).o: $(SRC)/%.cpp DIRS
	$(CXX) $(CXXFLAGS) $(CXXFLAGS_$(CONFIG)) $< -c -o $@ -I$(INCLUDE)


# Directory creation #
DIRS:
	mkdir -p $(BIN) $(OBJ) $(OUT)

# Clean #
clean: clean-$(BIN) clean-$(OBJ) clean-$(OUT) clean-$(DEB)

clean-$(BIN):
	-rm -f $(BIN)/*
clean-$(OBJ):
	-rm -f $(OBJ)/*
clean-$(OUT):
	-rm -f $(OUT)/*
clean-$(DEB):
	-rm -rf $(DEB)


uninstall:
	-rm -f /$(EXE_PATH)
	-rm -rf /$(INSTALL_PATH)

install: uninstall
	cp $(BIN)/$(EXE)-$(RELEASE) /$(EXE_PATH)
	-mkdir /$(INSTALL_PATH)
	-cp -rf lua/ /$(INSTALL_PATH)
	-cp -rf res/ /$(INSTALL_PATH)


deb: $(RELEASE) DIRS
	mkdir -p $(DEB)/$(BASE_PATH)/bin/ $(DEB)/$(INSTALL_PATH) $(DEB)/DEBIAN/
	cp $(BIN)/$(EXE)-$(RELEASE) $(DEB)/$(EXE_PATH)
	cp control $(DEB)/DEBIAN/
	cp -rf lua/ $(DEB)/$(INSTALL_PATH)
	cp -rf res/ $(DEB)/$(INSTALL_PATH)
	dpkg-deb -b $(DEB) $(OUT)/$(EXE).deb
	$(MAKE) clean-$(OBJ) clean-$(DEB)