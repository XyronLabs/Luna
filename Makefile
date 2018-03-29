# Directories #
BIN 	:= binaries
DEB     := deb
INCLUDE := include
OBJ 	:= objects
OUT 	:= $(BIN)/output
SRC 	:= source
LIB 	:= libraries


# Configurations #
STANDALONE	:= standalone
RELEASE		:= release
DEBUG		:= debug

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
LDFLAGS                := "-Wl,-rpath,./res/extlibs"
CXXFLAGS               := -std=c++14 -Wall
CXXFLAGS_$(RELEASE)    := -O3
CXXFLAGS_$(STANDALONE) := -O3 -DLUNA_STANDALONE
CXXFLAGS_$(DEBUG)      := -DLUNA_DEBUG



#----------------------------  Targets  ----------------------------#

all: $(CONFIG)

#-- Shortcuts --#
s:
	$(MAKE) -j8 CONFIG=standalone
r:
	$(MAKE) -j8 CONFIG=release
d:
	$(MAKE) -j8 CONFIG=debug
o:
	$(MAKE) -j8 deb


#-------------------------------------------------------------------#
#                           Configuration                           #
#-------------------------------------------------------------------#
$(CONFIG): $(objects-$(CONFIG)) DIRS
	$(CXX) $(objects-$(CONFIG)) -o $(BIN)/$@/$(EXE) $(LDFLAGS) -L$(LIB) $(libraries)

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
	-cp -rf res/ /$(INSTALL_PATH)


deb: $(RELEASE) DIRS
	mkdir -p $(DEB)/$(BASE_PATH)/bin/ $(DEB)/$(INSTALL_PATH) $(DEB)/DEBIAN/
	cp $(BIN)/$(EXE)-$(RELEASE) $(DEB)/$(EXE_PATH)
	cp build/debian/control $(DEB)/DEBIAN/
	cp -rf res/ $(DEB)/$(INSTALL_PATH)
	dpkg-deb -b $(DEB) $(OUT)/$(EXE).deb
	$(MAKE) clean-$(OBJ) clean-$(DEB)