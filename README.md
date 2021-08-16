# srt-editor


Simple srt file editing tool created to aid in my manual modification (and occasional creation) of subtitle files.


### Usage
In order to use this application, drop the srt files you want to edit using the program into the "srt-files" folder.
After running the program on one file, an edited file, aptly named "'original-file-name'-edited.srt" will be created.

#### Building
Navigate to the src folder and make:

***make*** (if on an unix-based system)

***mingw32-make.exe*** (if on windows, using gnu make)

#### Running
To run the program, simply run the following command from a terminal, while inside the src folder:

Unix-based: ***./srt-editor +/- hh:mm:ss:msc srtFile***

Windows:    ***srt-editor.exe +/- hh:mm:ss:msc srtFile***


Where:

    -hh, mm, ss and msc are the offset to add to the hours, minutes, seconds and milisseconds, respectively

    -srtFile is the name of the subtitle file you want to edit, inside the srt-files folder. It is not the relative path to the folder, nor an absolute path.


#### Notes
Line endings will be preserved, save for the line with the timestamps. The line ending in each timestamp will follow the conventions for the OS this program is run in.
Eventually, I'll take the time to fix this, but it shouldn't cause any issues whatsoever.