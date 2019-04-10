BIN=./bin/
BUILD=./build/

LIBS    = -lglut -lGLU -lGL -lm
CFLAGS  = -g
LFLAGS  = $(LIBS)

# Main targets
$(BIN)/new-drag: new-drag.o
	gcc -o new-drag new-drag.o $(LFLAGS)

# Source targets
$(BUILD)/new-drag.o: new-drag.c
	gcc -c new-drag.c $(CFLAGS)