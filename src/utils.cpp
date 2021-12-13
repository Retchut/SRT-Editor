#include "utils.h"

#include <iostream>
#include <sstream>
#include <string.h>

const std::vector<std::string> menuOptions = {
    "1 - Add Offset\n",
    "2 - Check sub IDs\n",
    "0 - Quit the application\n"
};

void printUsage(){
    std::cout << "Usage:\n";
    std::cout << "\t./srt-editor srtFile\n";
}

unsigned int cli(){
    printMenu();

    unsigned int option = 255;

    while(true){
        std::cout << "\nPlease input your desired option: ";
        std::string input = "";
        std::getline(std::cin, input);

        try{
            option = std::stoi(input);
        } catch (std::invalid_argument const&) {
            std::cout << "Please input an integer.\n";
            continue;
        }
        if(!(option < menuOptions.size())){
            std::cout << "That is not a valid option.\n";
        }
        else break;
    }
    return option;
}

void printMenu(){
    std::cout << std::endl;
    for(auto &option : menuOptions){
        std::cout << option;
    }
}

int getOffsets(int *offsets, int *start, int *end){
    std::string input;
    std::string originalOffset, originalStart, originalEnd, originalName;

    std::cout << "\nPlease insert the operation you want to apply ( (+)/(-) - addition/subtraction ): ";
    std::getline(std::cin, input);
    if(strcmp(input.c_str(), "+") && strcmp(input.c_str(), "-")){
        std::cout << "Invalid operation.\n";
        return 1;
    }
    int operation = (strcmp(input.c_str(), "+") == 0) ? 1 : -1;

    std::cout << "\nPlease insert the offset you wish to add (in the format <hh:mm:ss:msc>): ";
    std::getline(std::cin, originalOffset);
    std::vector<std::string> strOffsets = splitString(originalOffset, ":");
    if(strOffsets.size() != 4){
        std::cout << "Invalid offset.\n";
        return 1;
    }

    std::cout << "\nPlease insert the starting timestamp (in the format <hh:mm:ss:msc>; nothing to modify from the start): ";
    std::getline(std::cin, originalStart);
    if(strcmp(originalStart.c_str(), "") == 0) originalStart = "0:0:0:0";
    std::vector<std::string> strStart = splitString(originalStart, ":");
    if(strStart.size() != 4){
        std::cout << "Invalid offset.\n";
        return 1;
    }

    std::cout << "\nPlease insert the ending timestamp (in the format <hh:mm:ss:msc>; nothing to modify until the end): ";
    std::getline(std::cin, originalEnd);
    if(strcmp(originalEnd.c_str(), "") == 0) originalEnd = "59:59:59:999";
    std::vector<std::string> strEnd = splitString(originalEnd, ":");
    if(strEnd.size() != 4){
        std::cout << "Invalid offset.\n";
        return 1;
    }

    for(size_t i = 0; i < 4; i++){
        offsets[i] = operation * stoi(strOffsets[i]);
        start[i] = stoi(strStart[i]);
        end[i] = stoi(strEnd[i]);
    }

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