#include <sstream>
#include <iostream>

#include "utils.h"

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