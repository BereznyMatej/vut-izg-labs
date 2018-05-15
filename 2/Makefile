################################################################################
# IZG project, framework compilation
################################################################################


################################################################################
# promenne prekladu

CC = g++
CFLAGS = -g3 -Wall $(INCS) -Wno-unused-function -fmessage-length=0

ifeq ($(OS), Windows_NT)
    INCS = -I../SDL-1.2.15/include -IQ:/mingw/SDL/SDL
    LIBS = -lmingw32 -lSDLmain -lSDL -L../SDL-1.2.15/lib -LQ:/mingw/SDL
    REMOVE = rm -f
    BIN = izg_lab_02.exe
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
    BIN = izg_lab_02
endif


################################################################################
# obecny cil kompilace
.PHONY: all
all: $(BIN)


################################################################################
# linkovani vysledneho souboru
$(BIN):	main.o student.o io.o color.o
	$(CC) main.o student.o io.o color.o -o $(BIN) $(LIBS)


################################################################################
# kompilace hlavniho souboru
main.o: main.cpp
	$(CC) -c main.cpp -o main.o $(CFLAGS)


################################################################################
# kompilace studentskeho souboru
student.o: student.cpp student.h
	$(CC) -c student.cpp -o student.o $(CFLAGS)


################################################################################
# kompilace dilcich souboru
io.o: io.cpp io.h
	$(CC) -c io.cpp -o io.o $(CFLAGS)

color.o: color.cpp color.h
	$(CC) -c color.cpp -o color.o $(CFLAGS)


################################################################################
# cil vycisteni souboru prekladu
.PHONY: clear
clear:
	$(REMOVE) *.o $(BIN)


################################################################################
################################################################################
