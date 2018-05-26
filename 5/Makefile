################################################################################
# IZG lab #05, framework compilation
################################################################################


################################################################################
# build variables

CXX = g++
CXXFLAGS = $(INCS) -g3 -Wall

ifeq ($(OS), Windows_NT)
    INCS = -I../SDL-1.2.15/include -IQ:/mingw/SDL/SDL
    LIBS = -lmingw32 -lSDLmain -lSDL -L../SDL-1.2.15/lib -LQ:/mingw/SDL
    REMOVE = del
    BIN = izg_lab_05.exe
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
    BIN = izg_lab_05
endif


################################################################################
# build target
.PHONY: all
all: $(BIN)


################################################################################
# linking target file
$(BIN): main.o student.o transform.o model.o
	$(CXX) $^ -o $@ $(LIBS)


################################################################################
# building main file
main.o: src/main.cpp src/main.h
	$(CXX) -c $< -o $@ $(CXXFLAGS)


################################################################################
# building students file
student.o: src/student.cpp src/main.h
	$(CXX) -c $< -o $@ $(CXXFLAGS)


################################################################################
# building other files
transform.o: src/transform.cpp src/transform.h
	$(CXX) -c $< -o $@ $(CXXFLAGS)

model.o: src/model.cpp src/model.h
	$(CXX) -c $< -o $@ $(CXXFLAGS)


################################################################################
# clean built files
.PHONY: clear
clear:
	$(REMOVE) *.o $(BIN)


################################################################################
################################################################################
