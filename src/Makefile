CC = g++
CFLAGS = -c -Wall

all: offsetter.o
	$(CC) offsetter.o -o srt-editor

offsetter.o: offsetter.cpp
	$(CC) $(CFLAGS) offsetter.cpp

clean:
	rm *.o
	rm srt-editor