CC=gcc 
CFLAGS= -Wall
EXEC= morpion
INCFLACGS=`pkg-config --cflags --libs sdl2 sdl2_image`
#-I./glad/include -I/Library/Frameworks/SDL2.framework/Headers  -F/Library/Frameworks -framework SDL2 
OBJ= affiche.o click.o rendering.o

.PHONY: all $(OBJ) $(EXEC) 

all: $(EXEC)

affiche.o: affiche.c
	$(CC) $(INCFLACGS) -c $<

click.o: click.c
	$(CC) $(INCFLACGS) -c $<

rendering.o: rendering.c
	$(CC) $(INCFLACGS) -c $<

$(EXEC): $(OBJ)
	$(CC) $(INCFLACGS) -o $@ $(OBJ)
 
clean: 
	rm -f $(EXEC) && rm -f *.o

