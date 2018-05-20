################################################################################
# IZG project, framework compilation
################################################################################


################################################################################
# promenne prekladu

CXX = g++
CXXFLAGS = -g3 -Wall $(INCS) -Wno-unused-function -fmessage-length=0

ifeq ($(OS), Windows_NT)
    INCS = -I../SDL-1.2.15/include -IQ:/mingw/SDL/SDL
    LIBS = -lmingw32 -lSDLmain -lSDL -L../SDL-1.2.15/lib -LQ:/mingw/SDL
    REMOVE = rm -f
    BIN = izg_lab_03.exe
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S), Linux)
        LIBS = -lSDL
    else ifeq ($(UNAME_S), Darwin)
        LIBS = `sdl-config --libs`
        CXXFLAGS += `sdl-config --cflags`
    endif
    INCS = -I/usr/include/SDL
    REMOVE = rm -f
    BIN = izg_lab_03
endif


################################################################################
# obecny cil kompilace
.PHONY: all
all: $(BIN)


################################################################################
# linkovani vysledneho souboru
$(BIN): main.o student.o io.o color.o
	$(CXX) $^ -o $@ $(LIBS)


################################################################################
# kompilace hlavniho souboru
main.o: src/main.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)


################################################################################
# kompilace studentskeho souboru
student.o: src/student.cpp src/student.h
	$(CXX) -c $< -o $@ $(CXXFLAGS)


################################################################################
# kompilace dilcich souboru
io.o: src/io.cpp src/io.h
	$(CXX) -c $< -o $@ $(CXXFLAGS)

color.o: src/color.cpp src/color.h
	$(CXX) -c $< -o $@ $(CXXFLAGS)


################################################################################
# cil vycisteni souboru prekladu
.PHONY: clear
clear:
	$(REMOVE) *.o $(BIN)


################################################################################
################################################################################
