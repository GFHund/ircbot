CC=gcc

sqlite.so:
	$(CC) -o $@ sqlite.c -lsqlite3 -shared -fpic
	
clean:
	rm sqlite.so