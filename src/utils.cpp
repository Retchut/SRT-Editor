#include <sstream>
#include <iostream>
#include <vector>

#include "utils.h"

void printUsage(){
    std::cout << "Usage:\n";
    std::cout << "\t./srt-editor srtFile\n";
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

std::string getOtherFile(){
    std::string input;
    std::cout << "\nPlease input the name of the file you want to compare to: ";
    std::getline(std::cin, input);
    return input;
}