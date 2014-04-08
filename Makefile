CC = gcc

CFLAGS  = -g -Wall $(shell pkg-config --cflags cunit)

LDFLAGS = $(shell pkg-config --libs cunit)

testpoker: testpoker.o card.o hand.o

card.o: card.c card.h

hand.o: hand.c card.h hand.h

.PHONY: clean
clean:
	rm -f *.o *~ *.swp *.swo a.out core testpoker

.PHONY: all
all: clean testpoker
