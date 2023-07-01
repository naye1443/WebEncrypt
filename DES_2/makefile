CC=g++
# Pass debug options to compiler
CFLAGS= -I ./include -c -Wall -g

DES: DES.o test.o BCM.o Binary.o
	$(CC) DES.o test.o BCM.o Binary.o -o DES

DES.o: ./src/DES.cpp
	$(CC) $(CFLAGS) ./src/DES.cpp

test.o: ./src/test.cpp
	$(CC) $(CFLAGS) ./src/test.cpp

BCM.o: ./src/BCM.cpp
	$(CC) $(CFLAGS) ./src/BCM.cpp

Binary.o: ./src/Binary.cpp
	$(CC) $(CFLAGS) ./src/Binary.cpp

clean:
	rm -rf *.o