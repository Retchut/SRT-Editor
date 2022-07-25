#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>

#include "timestamp-diff.h"
#include "utils.h"

void findDiff(std::string fileName){
    std::string compare = getOtherFile();
    std::ifstream toCompare;
    if(toCompare.fail()){
        std::cout << "\nThat file does not exist.\n";
        return;
    }
    std::ifstream original(fileName);

    std::string lineOriginal;
    std::string lineCompare;
    unsigned int expectedID = 1;
    bool incorrectIDS = false;
    std::vector<int> timestampDiffs;

    while(std::getline(original, lineOriginal)){
        if(!toCompare.good()){
            std::cout << "\nThe files are not the same length.";
            original.close();
            toCompare.close();
            return;
        }
        std::getline(toCompare, lineCompare);
        
        // if we read a new line on both files
        if(!isNewLine(lineOriginal) && !isNewLine(lineCompare)){
            //id line
            std::stringstream ssOriginal(lineOriginal);
            std::stringstream ssCompare(lineCompare);
            unsigned int subIDOriginal = 0;
            unsigned int subIDCompare = 0;
            ssOriginal >> subIDOriginal;
            ssCompare >> subIDCompare;

            if(subIDOriginal != subIDCompare){
                std::cout << "\nThe files' subtitle IDs are not the same. Please make sure they are before running this tool.";
                original.close();
                toCompare.close();
                return;
            }

            //if the ids are not already flagged as incorrect, check them and update the flag as necessary
            if(!incorrectIDS && (subIDOriginal != expectedID)){
                incorrectIDS = true;
            }
            expectedID++;

            //timestamp line
            std::getline(original, lineOriginal);
            std::getline(toCompare, lineCompare);
            if(lineOriginal != lineCompare){
                timestampDiffs.push_back(subIDOriginal);
            }

            //skip text on the original file
            while(!(isNewLine(lineOriginal))){
                if(!std::getline(original, lineOriginal))
                    break;
            }
            //skip text on the comparison file
            while(!(isNewLine(lineOriginal))){
                if(!std::getline(original, lineOriginal))
                    break;
            }
        }
    }

    toCompare.close();
    original.close();

    std::cout << "\nThe following subtitles have different timestamps: ";
    for(unsigned int i = 0; i < timestampDiffs.size(); i++){
        std::cout << timestampDiffs[i];
    }

    if(incorrectIDS){
        std::cout << "\n\nAdditionally, the ids on both subtitle files are not in order. It is a good idea to fix that.\n";
    }
}

std::string getOtherFile(){
    std::string input;
    std::cout << "\nPlease input the name of the file you want to compare to: ";
    std::getline(std::cin, input);
    return input;
}