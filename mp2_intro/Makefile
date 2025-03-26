EXE = intro
OBJS = main.o png.o rgbapixel.o intro.o
SRC = RGBA
COMPILER = g++ 
COMPILER_OPTS = -std=c++17 -c -g -O0  -pedantic-errors 
LINKER = g++
LINKER_OPTS = -lpng

all : $(EXE)

$(EXE) : $(OBJS)
	$(LINKER) $(OBJS) $(LINKER_OPTS) -o $(EXE)

main.o : main.cpp intro.h $(SRC)/png.h $(SRC)/rgbapixel.h
	$(COMPILER) $(COMPILER_OPTS) main.cpp

intro.o : intro.cpp intro.h $(SRC)/png.h $(SRC)/rgbapixel.h
	$(COMPILER) $(COMPILER_OPTS) intro.cpp

png.o : $(SRC)/png.cpp $(SRC)/png.h $(SRC)/rgbapixel.h
	$(COMPILER) $(COMPILER_OPTS) $(SRC)/png.cpp

rgbapixel.o : $(SRC)/rgbapixel.cpp $(SRC)/rgbapixel.h
	$(COMPILER) $(COMPILER_OPTS) $(SRC)/rgbapixel.cpp

clean :
	-rm -f *.o $(EXE)
