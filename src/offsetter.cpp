#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>

#include "offsetter.h"
#include "utils.h"

int main(int argc, char *argv[]){
    if(argc < 6 || argc > 6){   //eventually I'll allow editing multiple files
        printUsage();
        return 1;
    }

    std::string fileName = "../srt-files/";
    fileName.append(argv[5]);
    addOffset(fileName, std::stoi(argv[1]), std::stoi(argv[2]), std::stoi(argv[3]), std::stoi(argv[4]));

    return 0;
}

void addOffset(std::string subFile, int h, int m, int s, int ms){
    //TODO(if I decide to not be lazy): instead of creating a new file, backup the and edit the old one
    std::string newName = subFile;
    newName.insert(newName.size()-4, "-edited");

    //open file from reading and new file for writing to
    std::ifstream oldFile(subFile);
    std::ofstream newFile(newName);

    std::string line;
    while(std::getline(oldFile, line)){
        line.append("\n");  //getline ignores \n
        if(isNewLine(line)){
            newFile << line;
        }
        else{
            //write id line
            newFile << line;
            //treat timestamp line
            std::getline(oldFile, line);
            editTimestamp(line, h, m, s, ms);
            newFile << line;

            //treat text
            while(!(isNewLine(line))){
                if(!std::getline(oldFile, line))
                    break;
                line.append("\n");  //getline ignores \n
                newFile << line;
            }
        }
    }

    newFile.close();
    oldFile.close();
}

void editTimestamp(std::string &old, int h, int m, int s, int ms){
    std::stringstream ss;
    std::vector<std::string> times = splitString(old, ":, ");    

    ss << std::setfill('0') << std::setw(5);

    int stampNum = 0;
    for(size_t i = 0; i < 3; i++){
        if(i == 1){    //arrow
            ss << " " << times[4] << " ";
        }
        else{
            //TODO: clean up this mess, god it hurts my eyes
            int timeStamps[4] = {
                std::stoi(times[stampNum*5+0]), std::stoi(times[stampNum*5+1]),
                    std::stoi(times[stampNum*5+2]), std::stoi(times[stampNum*5+3])        
                                };
            int offsets[4] = {h, m, s, ms};
            char delimiters[3] = {':', ':', ','};

            for(size_t i = 0; i < 3; i++){
                int newTime = timeStamps[i] + offsets[i];
                ss << std::setfill('0') << std::setw(2) << newTime << delimiters[i];
            }

            int newTime = timeStamps[3] + offsets[3];
            ss << std::setfill('0') << std::setw(3) << newTime;

            stampNum++;
        }
    }
    ss << "\n";
    
    old = ss.str();
}
