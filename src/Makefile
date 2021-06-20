CC = g++
CFLAGS = -c -Wall

ifeq ($(OS),Windows_NT)
	EXECUTABLE=srt-editor.exe
	DELETE=del /f
else
	EXECUTABLE=srt-editor
	DELETE=rm -f
endif

all: offsetter.o utils.o
	$(CC) offsetter.o utils.o -o $(EXECUTABLE)

offsetter.o: offsetter.cpp utils.cpp
	$(CC) $(CFLAGS) offsetter.cpp utils.cpp

clean:
	-$(DELETE) *.o srt-editor srt-editor.exe