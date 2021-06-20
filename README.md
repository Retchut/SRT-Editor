# srt-editor


Simple srt file editing tool created to aid in my manual modification (and occasional creation) of subtitle files.


#### Usage
In order to use this application, create a folder called "srt-files" on the root directory of the repo. This will be where you drop the srt files you can later edit using the program.

Navigate to the src folder and make:

***make*** (if on an unix-based system)

***mingw32-make.exe*** (if on windows, using gnu make)

To run the program, simply run the following command from a terminal, while inside the src folder:

***./srt-editor hourOffset minOffset secOffset msecOffset srtFile***

or

***srt-editor.exe hourOffset minOffset secOffset msecOffset srtFile***

if on windows


Where:

    -xOffset is the offset to add to x

    -srtFile is the name of the subtitle file you want to edit, inside the srt-files folder. It is not the relative path to the folder, nor an absolute path.


#### Notes
If the srt file contains unix styled line endings, each line ending after the time stamps of each subtitle will be replaced with windows styled line endings. In all other cases, the line endings are preserved.
Eventually, I'll take the time to fix this, but it shouldn't cause any issues whatsoever.