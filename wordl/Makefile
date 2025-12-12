CC = gcc
CFLAGS = -O2 -Wall -std=c99

OBJS = main.o game.o score.o

all: wordle.exe

wordle.exe: $(OBJS)
	$(CC) $(CFLAGS) -o wordle.exe $(OBJS)

main.o: main.c score.h
	$(CC) $(CFLAGS) -c main.c

game.o: game.c score.h
	$(CC) $(CFLAGS) -c game.c

score.o: score.c score.h
	$(CC) $(CFLAGS) -c score.c

clean:
	del /Q *.o wordle.exe scores.json

.PHONY: all clean
