################################################################################
# IZG project, framework compilation
################################################################################


################################################################################
# promenne prekladu

CC = gcc
CFLAGS = -g3 -Wall $(INCS) -Wno-unused-function -fmessage-length=0

ifeq ($(OS), Windows_NT)
    INCS = -I../SDL-1.2.15/include -IQ:/mingw/SDL/SDL
    LIBS = -lmingw32 -lSDLmain -lSDL -L../SDL-1.2.15/lib -LQ:/mingw/SDL
    REMOVE = rm -f
    BIN = izg_lab_01.exe
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S), Linux)
        LIBS = -lSDL
    else ifeq ($(UNAME_S), Darwin)
        LIBS = `sdl-config --libs`
        CFLAGS += `sdl-config --cflags`
    endif
    INCS = -I/usr/include/SDL
    REMOVE = rm -f
    BIN = izg_lab_01
endif


################################################################################
# obecny cil kompilace
.PHONY: all
all: $(BIN)


################################################################################
# linkovani vysledneho souboru
$(BIN): main.o student.o io.o color.o
	$(CC) $^ -o $@ $(LIBS)


################################################################################
# kompilace hlavniho souboru
main.o: main.c
	$(CC) -c $< -o $@ $(CFLAGS)


################################################################################
# kompilace studentskeho souboru
student.o: student.c student.h
	$(CC) -c $< -o $@ $(CFLAGS)


################################################################################
# kompilace dilcich souboru
io.o: io.c io.h
	$(CC) -c $< -o $@ $(CFLAGS)

color.o: color.c color.h
	$(CC) -c $< -o $@ $(CFLAGS)


################################################################################
# cil vycisteni souboru prekladu
.PHONY: clear
clear:
	$(REMOVE) *.o $(BIN)


################################################################################
################################################################################
