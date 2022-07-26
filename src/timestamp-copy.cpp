#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>

#include "timestamp-copy.h"
#include "utils.h"

void copyTimestamps(std::string fileName){
    std::string newName = fileName;
    newName.insert(newName.size()-4, "-edited");
    std::ofstream newFile(newName);

    std::string compare = getOtherFile();
    std::ifstream toCompare(compare);
    if(toCompare.fail()){
        std::cout << "\nThat file does not exist.\n";
        return;
    }
    std::ifstream original(fileName);

    std::string lineOriginal;
    std::string lineCompare;
    unsigned int expectedID = 1;
    bool incorrectIDS = false;

    while(std::getline(original, lineOriginal)){
        std::getline(toCompare, lineCompare);

        lineOriginal.append("\n");  //getline ignores \n
        if(isNewLine(lineOriginal) && isNewLine(lineCompare)){
            newFile << lineOriginal;
        }
        else{
            //id line
            std::stringstream ssOriginal(lineOriginal);
            std::stringstream ssCompare(lineCompare);
            unsigned int subIDOriginal = 0;
            unsigned int subIDCompare = 0;
            ssOriginal >> subIDOriginal;
            ssCompare >> subIDCompare;

            if(subIDCompare == 0){
                std::cout << "\nThe comparison file is shorter. Please make sure both files have the same number of subtitles before running this tool.\n";
                original.close();
                toCompare.close();
                newFile.close();
                return;
            }

            if(subIDOriginal != subIDCompare){
                std::cout << "\nThe files' subtitle IDs are not the same (" << subIDOriginal << "/" << subIDCompare << ", original/comparison). Please make sure they are before running this tool.\n";
                original.close();
                toCompare.close();
                newFile.close();
                return;
            }

            //if the ids are not already flagged as incorrect, check them and update the flag as necessary
            if(!incorrectIDS && (subIDOriginal != expectedID)){
                incorrectIDS = true;
            }
            newFile << lineOriginal;
            expectedID++;

            //timestamp line
            std::getline(original, lineOriginal);
            std::getline(toCompare, lineCompare);
            lineOriginal.append("\n");  //getline ignores \n
            lineCompare.append("\n");  //getline ignores \n
            newFile << lineCompare;

            //skip text on the original file
            while(!(isNewLine(lineOriginal))){
                if(!std::getline(original, lineOriginal))
                    break;
                lineOriginal.append("\n");  //getline ignores \n
                newFile << lineOriginal;
            }
            //skip text on the comparison file
            while(!(isNewLine(lineCompare))){
                if(!std::getline(toCompare, lineCompare))
                    break;
                lineCompare.append("\n");  //getline ignores \n
            }
        }
    }

    // read remaining line on the comparison file
    std::getline(toCompare, lineCompare);
    if(!toCompare.eof()){
        std::cout << "\nThe original file is shorter. Please make sure both files have the same number of subtitles before running this tool.\n";
        toCompare.close();
        original.close();
        newFile.close();
        return;
    }

    toCompare.close();
    original.close();
    newFile.close();

    if(incorrectIDS){
        std::cout << "\n\nAdditionally, the ids on both subtitle files are not in order. It is a good idea to fix that.\n";
    }

    std::cout << std::endl;
}