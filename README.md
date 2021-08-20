
# srt-editor


Simple srt file editing tool created to aid in my manual modification (and occasional creation) of subtitle files.

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

After running the program on one file, an edited file, aptly named "'original-file-name'-edited.srt" will be created on the same directory as the original file.

## Notes
	-hh, mm, ss and msc are the offset to add to the hours, minutes, seconds and milisseconds, respectively

	-srtFile is either the relative path to the file, or an absolute path to the file you want to edit.

	-on windows, replace *srt-editor* with *srt-editor.exe*

Line endings will be preserved, save for the line with the timestamps. The line ending in each timestamp will follow the conventions for the OS this program is run in.
Eventually, I'll take the time to fix this, but it shouldn't cause any issues whatsoever.

##TODO

---> Clean up "modular arithmetic-like" code up (I was sleep deprived while writing it, don't judge)
---> Change all files in directory if the path provided was a directory;
---> Maybe maybe maybe add an option to overwrite the old file;
---> Add utility to create an empty subtitle at any timestamp (taken up by another sub or not);
---> Simple cli to allow selecting the utility to be used;
