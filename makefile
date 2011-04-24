CC=g++
FLAGS = -Wall -pedantic -ansi


PHIIRC: irc.o plugin.o
	$(CC) -o $@ main.cpp phiirc.h phiirc.cpp irc.o plugin.o
	
#main.o: phiirc.o
#	$(CC) -c main.cpp phiirc.o
	
irc.o: 
	$(CC) -c irc.h irc.cpp irc.o
	
plugin:
	$(CC) -cc plugin.h plugin.cpp -ldl
	

test: 
	$(CC) $(FLAGS) main.cpp phiirc.h phiirc.cpp irc.h irc.cpp plugin.h plugin.cpp -o phiirc

sqlite.so:
	cd ./Plugins/sqlite
	gcc -o sqlite.so sqlite.c -shared -fpic
	cd ../../


debug:
	
debugTest:
	$(CC) -g $(FLAGS) main.cpp phiirc.h phiirc.cpp irc.h irc.cpp -o phiirc

clean:
	rm *.o
	rm PHIIRC