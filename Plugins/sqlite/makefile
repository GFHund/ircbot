CC=gcc
FLAGS = -Wall -pedantic -ansi
sqlite.so:
	$(CC) -o $@ $(FLAGS) sqlite.c -lsqlite3 -shared -fpic
	
clean:
	rm sqlite.so
