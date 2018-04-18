CC = g++
CFLAGS = -c -O3 -std=c++11

all: lzw.o
	$(CC) -o lzw lzw.o CompressTree.o DecompressTree.o LzwReader.o LzwWriter.o
	rm -f *.o

lzw.o: main.cpp CompressTree.o DecompressTree.o LzwReader.o LzwWriter.o
	$(CC) $(CFLAGS) main.cpp -o lzw.o
	
CompressTree.o: CompressTree.h CompressTree.cpp
	$(CC) $(CFLAGS) CompressTree.cpp -o CompressTree.o
	
DecompressTree.o: DecompressTree.h DecompressTree.cpp
	$(CC) $(CFLAGS) DecompressTree.cpp -o DecompressTree.o
	
LzwReader.o: LzwReader.h LzwReader.cpp
	$(CC) $(CFLAGS) LzwReader.cpp -o LzwReader.o

LzwWriter.o: LzwWriter.h LzwWriter.cpp
	$(CC) $(CFLAGS) LzwWriter.cpp -o LzwWriter.o

clean:
	rm -f *.o lzw
