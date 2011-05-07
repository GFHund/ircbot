CC=g++
FLAGS = -Wall -pedantic -ansi


PHIIRC: irc.o plugin.o
	$(CC) -o $@ $(FLAGS) main.cpp phiirc.h phiirc.cpp irc.o plugin.o -ldl
	
#main.o: phiirc.o
#	$(CC) -c main.cpp phiirc.o
	
irc.o: 
	$(CC) -c irc.h irc.cpp
	
plugin.o:
	$(CC) -c plugin.h plugin.cpp 
	

test: 
	$(CC) $(FLAGS) main.cpp phiirc.h phiirc.cpp irc.h irc.cpp plugin.h plugin.cpp -o phiirc



debug: irc.o plugin.o
	$(CC) -g -o $@ main.cpp phiirc.h phiirc.cpp irc.o plugin.o -ldl
	
debugTest:
	$(CC) -g $(FLAGS) main.cpp phiirc.h phiirc.cpp irc.h irc.cpp -o phiirc

clean:
	rm *.o
	rm PHIIRC
	rm debug