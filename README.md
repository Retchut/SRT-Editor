# srt-editor


Simple srt file editing tool created to aid in my manual modification (and occasional creation) of subtitle files.


## Usage
In order to use this application, drop the srt files you want to edit using the program into the "srt-files" folder.
After running the program on one file, an edited file, aptly named "'original-file-name'-edited.srt" will be created.

## Building
Navigate to the src folder and make:

***make*** (if on an unix-based system)

***mingw32-make.exe*** (if on windows, using gnu make)

## Running
To run the program, simply run one of the following commands from a terminal, while inside the src folder:

>./srt-editor +/- hh:mm:ss:msc h1:m1:s1:ms1 h2:m2:s2:ms2 srtFile

***adds/subtracts hh:mm:ss:msc to all subtitles on srtFile beginning between h1:m1:s1:ms1 and h2:m2:s2:ms2 (inclusive)***

>./srt-editor +/- hh:mm:ss:msc srtFile

***adds/subtracts hh:mm:ss:msc to all subtitles on srtFile***


## Notes
	-hh, mm, ss and msc are the offset to add to the hours, minutes, seconds and milisseconds, respectively

	-srtFile is the name of the subtitle file you want to edit, inside the srt-files folder (including the file extension). It is not the relative path to the folder, nor an absolute path.

	-on windows, replace *srt-editor* with *srt-editor.exe*

Line endings will be preserved, save for the line with the timestamps. The line ending in each timestamp will follow the conventions for the OS this program is run in.
Eventually, I'll take the time to fix this, but it shouldn't cause any issues whatsoever.
