CC=g++
# Pass debug options to compiler
CFLAGS= -I ./include -c -Wall -g

DES: DES.o test.o
	$(CC) DES.o test.o -o DES

DES.o: ./src/DES.cpp
	$(CC) $(CFLAGS) ./src/DES.cpp

test.o: ./src/test.cpp
	$(CC) $(CFLAGS) ./src/test.cpp

clean:
	rm -rf *.o