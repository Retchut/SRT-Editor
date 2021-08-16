#include "utils.h"

#include <iostream>
#include <sstream>
#include <string.h>

void printUsage(){
    std::cout << "Usage: ./srt-editor +/- hh:mm:ss:msc srtFile\n";
}

int *parseCommand(char *argv[]){
    static int offsets[4];
    int operation = (strcmp(argv[1], "+") == 0) ? 1 : -1;

    std::vector<std::string> inputOffset = splitString(argv[2], ":");

    for(size_t i = 0; i < 4; i++){
        offsets[i] = operation * stoi(inputOffset[i]);
    }

    return offsets;    
}

bool isNewLine(std::string compare){
    return compare == "\n" || compare == "\r\n";
}

//  Kindly appropriated from
//  https://stackoverflow.com/a/7621814
std::vector<std::string> splitString(std::string toSplit, std::string delimiters){
    std::stringstream ss(toSplit);
    std::string line;
    std::vector<std::string> words;
    while(std::getline(ss, line)) 
    {
        size_t prev = 0, pos;
        while ((pos = line.find_first_of(delimiters, prev)) != std::string::npos)
        {
            if (pos > prev)
                words.push_back(line.substr(prev, pos-prev));
            prev = pos+1;
        }
        if (prev < line.length())
            words.push_back(line.substr(prev, std::string::npos));
    }

    return words;
}