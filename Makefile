CC = gcc
CFlags = -std=c11 -D_XOPEN_SOURCE=700

.PHONY: all debug clean

all: main

main: main.o list.o input.o outputDir.o tags.o
	$(CC) $(CFlags) -o main main.o list.o input.o outputDir.o tags.o
	#$(CC) $(CFlags) -o $@  $^

%.o: %.c
	$(CC) $(CFlags) -c $<

main.o: input.h outputDir.h list.h tags.h

input.o: input.h

list.o : list.h

outputDir.o : list.h outputDir.h

tags.o : tags.h list.h

debug :all

debug: CFlags += -g

clean:
		 rm -f main *.o 
