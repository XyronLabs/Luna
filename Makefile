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
	$(CXX) $(CXXFLAGS) -O3 $(sources) -o $@ -I$(INCLUDE) $(libs)

debug: $(sources) $(BIN)
	$(CXX) $(CXXFLAGS) $(sources) -o $(BIN)/$(EXE)-$@ -I$(INCLUDE) $(libs) -DLUNA_DEBUG


$(BIN):
	mkdir $(BIN)

clean:
	-@rm $(BIN)/*

run: debug
	./$(BIN)/$(EXE)-debug


install:
	-rm /usr/local/bin/$(EXE)
	cp $(BIN)/$(EXE) /usr/local/bin/
	-mkdir /usr/local/luna
	-cp -rf lua/ /usr/local/luna/
	-cp -rf res/ /usr/local/luna/


deb: all
	mkdir -p deb/usr/local/bin/ deb/usr/local/luna/ deb/DEBIAN/
	cp $(BIN)/$(EXE) deb/usr/local/bin/
	cp control deb/DEBIAN/
	cp -rf lua/ deb/usr/local/luna/
	cp -rf res/ deb/usr/local/luna/
	dpkg-deb -b deb luna.deb
	rm -rf deb