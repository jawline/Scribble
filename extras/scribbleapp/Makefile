SOURCE_FILES=main.cpp
OUTPUT=./a.out
CFLAGS= -L ../../bin/ -lscribble -I ../../src/ -std=c++0x
CC = g++

all:
	$(CC) $(CFLAGS) $(SOURCE_FILES) -o $(OUTPUT)

clean:
	-rm $(OUTPUT)