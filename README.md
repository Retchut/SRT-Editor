# srt-editor


Simple srt file editing tool created to aid in my manual modification (and occasional creation) of subtitle files.


#### Usage
In order to use this application, create a folder called "srt-files" on the root directory of the repo. This will be where you drop the srt files you can later edit using the program.

Navigate to the src folder and make.

To run the program, simply run the following command from a terminal, while inside the src folder:

***./srt-editor hourOffset minOffset secOffset, msecOffset srtFile***

Where:

    -\<thing\>Offset is the offset to add to *thing*

    -srtFile is the name of the subtitle file you want to edit, inside the srt-files folder. It is not the relative path to the folder, nor an absolute path.


#### Notes
There is a high likelyhood that the program breaks if/when a subtitle sentence begins with a letter. I'll fix that when I'm less sleep deprived. For now, it does the work I need it to ^^