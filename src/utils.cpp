#include "utils.h"

#include <iostream>
#include <sstream>
#include <string.h>

void printUsage(){
    std::cout << "Usage:\n";
    std::cout << "-->edit from start to finish\n";
    std::cout << "\t./srt-editor +/- hh:mm:ss:msc srtFile\n";
    std::cout << "-->edit from h1:m1:s1:ms1 to h2:m2:s2:ms2 (inclusively)\n";
    std::cout << "\t./srt-editor +/- hh:mm:ss:msc h1:m1:s1:ms1 h2:m2:s2:ms2 srtFile\n";
}

int parseCommand(int argc, char *argv[], int *offsets, int *startInt, int *endInt, std::string *fileName){
    //if the input operation was not + or -
    if(strcmp(argv[1], "+") && strcmp(argv[1], "-")){
        std::cout << "Invalid operation. Supported operations are addition (+) and subtraction (-).\n";
        return 1;
    }

    int operation = (strcmp(argv[1], "+") == 0) ? 1 : -1;

    std::string originalOffset, originalStart, originalEnd, originalName;

    originalOffset = argv[2];
    if(argc == 4){
        originalStart = "0:0:0:0";
        originalEnd = "59:59:59:999";
        originalName = argv[3];
    }
    else if(argc == 6){
        originalStart = argv[3];
        originalEnd = argv[4];
        originalName = argv[5];
    }

    std::vector<std::string> strOffsets = splitString(originalOffset, ":");
    std::vector<std::string> strStart = splitString(originalStart, ":");
    std::vector<std::string> strEnd = splitString(originalEnd, ":");

    for(size_t i = 0; i < 4; i++){
        offsets[i] = operation * stoi(strOffsets[i]);
        startInt[i] = stoi(strStart[i]);
        endInt[i] = stoi(strEnd[i]);
    }
    
    //TODO catch error returnal
    fileName->append(originalName);

    return 0;
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