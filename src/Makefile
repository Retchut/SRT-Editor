CC = g++
CFLAGS = -c -Wall

ifeq ($(OS),Windows_NT)
	EXECUTABLE=srt-editor.exe
	DELETE=del /f
else
	EXECUTABLE=srt-editor
	DELETE=rm -f
endif

all: srt-editor.o utils.o
	$(CC) srt-editor.o utils.o -o $(EXECUTABLE)

srt-editor.o: srt-editor.cpp utils.cpp
	$(CC) $(CFLAGS) srt-editor.cpp utils.cpp

clean:
	-$(DELETE) *.o srt-editor srt-editor.exe