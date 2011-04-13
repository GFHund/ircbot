CC=g++
LIBIRCCLIENT=/home/tux/libs/libircclient-1.3


PHIIRC:
	$(CC) main.c -lircclient -L$(LIBIRCCLIENT)/src -I$(LIBIRCCLIENT)/include