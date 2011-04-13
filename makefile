CC=g++
LIBIRCCLIENT=/home/tux/libs/libircclient-1.3


PHIIRC:
	$(CC) -o $@ main.c -lircclient -L$(LIBIRCCLIENT)/src -I$(LIBIRCCLIENT)/include
	
phiirc.o:
	$(CC) -c -o $@ phiirc.h phiirc.cpp irc.o
	
irc.o:
	$(CC) -c  -o $@ irc.h irc.cpp