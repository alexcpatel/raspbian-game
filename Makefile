CC = gcc
CSDL = `sdl2-config --cflags` `sdl2-config --libs`
CFLAGS = -g -Wall -pedantic -std=c99
CALL = $(CC) $(CSDL) $(CFLAGS)

CUR = test

all: clean $(CUR)
$(CUR):
	$(CALL) -o $(CUR) $(CUR).c

.PHONY: clean
clean:
	rm $(CUR)