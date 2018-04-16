# Directories #
BIN 	:= binaries
DEB     := deb
INCLUDE := include
OBJ 	:= objects
OUT 	:= $(BIN)/output
SRC 	:= source/luna
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
libraries := -llua -ldl -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system

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
$(CONFIG): $(objects-$(CONFIG)) 
	$(CXX) $(objects-$(CONFIG)) -o $(BIN)/$@/$(EXE) $(LDFLAGS) -L$(LIB) $(libraries)

$(OBJ)/%-$(CONFIG).o: $(SRC)/%.cpp DIRS
	$(CXX) $(CXXFLAGS) $(CXXFLAGS_$(CONFIG)) $< -c -o $@ -I$(INCLUDE)


# Directory creation #
DIRS:
	mkdir -p $(BIN)/$(DEBUG) $(BIN)/$(RELEASE) $(BIN)/$(STANDALONE) $(OBJ) $(OUT)

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
	cp $(BIN)/$(RELEASE)/$(EXE) /$(EXE_PATH)
	-mkdir /$(INSTALL_PATH)
	-cp -rf resources/luna/ /$(INSTALL_PATH)/res


deb: $(RELEASE) DIRS
	mkdir -p $(DEB)/$(BASE_PATH)/bin/ $(DEB)/$(INSTALL_PATH) $(DEB)/DEBIAN/
	cp $(BIN)/$(RELEASE)/$(EXE) $(DEB)/$(EXE_PATH)
	cp resources/build/debian/control $(DEB)/DEBIAN/
	cp -rf resources/luna/ $(DEB)/$(INSTALL_PATH)/res
	dpkg-deb -b $(DEB) $(OUT)/$(EXE).deb
	$(MAKE) clean-$(OBJ) clean-$(DEB)