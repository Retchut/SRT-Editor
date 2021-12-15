CC = g++
CFLAGS = -c -Wall

ifeq ($(OS),Windows_NT)
	EXECUTABLE=srt-editor.exe
	DELETE=del /f
else
	EXECUTABLE=srt-editor
	DELETE=rm -f
endif

all: srt-editor.o utils.o offsetter.o check-id.o
	$(CC) srt-editor.o utils.o offsetter.o check-id.o -o $(EXECUTABLE)

srt-editor.o: srt-editor.cpp utils.cpp
	$(CC) $(CFLAGS) srt-editor.cpp utils.cpp

offsetter.o: offsetter.cpp utils.cpp
	$(CC) $(CFLAGS) offsetter.cpp utils.cpp

check-id.o: check-id.cpp utils.cpp
	$(CC) $(CFLAGS) check-id.cpp utils.cpp

clean:
	-$(DELETE) *.o srt-editor srt-editor.exe