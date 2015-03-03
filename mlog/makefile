all:test

CC=gcc
SRC=test.c mlog.c

test:
	$(CC) -g -o $@ $(SRC)

clean:
	rm -f test


#or:
#test:
#	$(CC) -o libmlog.so -fPIC -shared mlog.c
#	mv libmlog.so /usr/lib/
#	$(CC) -o $@ -lmlog test.c

