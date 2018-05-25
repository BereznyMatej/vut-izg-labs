################################################################################
# IZG project, framework compilation
################################################################################


################################################################################
# promenne prekladu

CXX = g++
CXXFLAGS = -std=c++11 -g3 -Wall $(INCS) -Wno-unused-function -fmessage-length=0
OBJ = main.o student.o vector.o color.o

ifeq ($(OS), Windows_NT)
    INCS = -I../SDL-1.2.15/include -IQ:/mingw/SDL/SDL
    LIBS = -lmingw32 -lSDLmain -lSDL -L../SDL-1.2.15/lib -LQ:/mingw/SDL
    CFLAGS += -m32
    REMOVE = del
    BIN = izg_lab_04.exe
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
    BIN = izg_lab_04
endif


%.o: %.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)


################################################################################
# obecny cil kompilace
.PHONY: all
all: $(BIN)


################################################################################
# linkovani vysledneho souboru
$(BIN): $(OBJ)
	$(CXX) $^ -o $@ $(LIBS) -lm


################################################################################
# cil vycisteni souboru prekladu
.PHONY: clear
clear:
	$(REMOVE) $(OBJ) $(BIN)


################################################################################
################################################################################
