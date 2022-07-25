CC = g++
CFLAGS = -c -Wall

ifeq ($(OS),Windows_NT)
	EXECUTABLE=srt-editor.exe
	DELETE=del /f
else
	EXECUTABLE=srt-editor
	DELETE=rm -f
endif

all: srt-editor.o utils.o offsetter.o check-id.o save-changes.o timestamp-diff.o
	$(CC) srt-editor.o utils.o offsetter.o check-id.o save-changes.o timestamp-diff.o -o $(EXECUTABLE)

srt-editor.o: srt-editor.cpp utils.cpp
	$(CC) $(CFLAGS) srt-editor.cpp utils.cpp

offsetter.o: offsetter.cpp utils.cpp
	$(CC) $(CFLAGS) offsetter.cpp utils.cpp

check-id.o: check-id.cpp utils.cpp
	$(CC) $(CFLAGS) check-id.cpp utils.cpp

save-changes.o: save-changes.cpp
	$(CC) $(CFLAGS) save-changes.cpp

timestamp-diff.o: timestamp-diff.cpp
	$(CC) $(CFLAGS) timestamp-diff.cpp

clean:
	-$(DELETE) *.o srt-editor srt-editor.exe