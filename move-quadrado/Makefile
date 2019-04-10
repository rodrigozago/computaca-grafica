LIBS    = -lglut -lGLU -lGL -lm
CFLAGS  = -g
LFLAGS  = $(LIBS)

# Main targets
new-drag: new-drag.o
	gcc -o new-drag new-drag.o $(LFLAGS)

# Source targets
new-drag.o: new-drag.c
	gcc -c new-drag.c $(CFLAGS)