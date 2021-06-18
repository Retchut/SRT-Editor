CC = g++
CFLAGS = -c -Wall

all: offsetter.o
	$(CC) offsetter.o utils.cpp -o srt-editor

offsetter.o: offsetter.cpp utils.cpp
	$(CC) $(CFLAGS) offsetter.cpp utils.cpp

clean:
	-rm srt-editor *.o