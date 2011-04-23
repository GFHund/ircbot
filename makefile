CC=g++
FLAGS = -Wall -pedantic -ansi


PHIIRC: phiirc.o
	$(CC) -o $@ main.cpp phiirc.o
	
#main.o: phiirc.o
#	$(CC) -c main.cpp phiirc.o
	
phiirc.o: irc.o
	$(CC) -c phiirc.h phiirc.cpp irc.h irc.cpp irc.o
	
#irc.o:
#	$(CC) -c   irc.h irc.cpp
	
test:
	$(CC) $(FLAGS) main.cpp phiirc.h phiirc.cpp irc.h irc.cpp -o phiirc

debug:

debugTest:
	$(CC) -g $(FLAGS) main.cpp phiirc.h phiirc.cpp irc.h irc.cpp -o phiirc

clean:
	rm *.o
	rm PHIIRC