IDIR = include
SDIR = src
ODIR = obj

CC = gcc
CFLAGS = `sdl2-config --cflags` -g -Wall -Werror -pedantic -std=c99 -I$(IDIR)
LIBS = -lSDL2 -lSDL2_image -lm

_DEPS = constants.h player.h texture.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = game.o player.o texture.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

game: clean $(ODIR) $(OBJ)
	$(CC) -o $@ $(OBJ) $(CFLAGS) $(LIBS)

$(ODIR)/%.o: $(SDIR)/%.c $(ODIR) $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(LIBS)

.PHONY: $(ODIR)
$(ODIR):
	mkdir $(ODIR)

.PHONY: clean
clean:
	rm -rf game $(ODIR) core *~ $(IDIR)/*~
