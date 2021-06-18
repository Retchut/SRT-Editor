#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "offsetter.h"
#include "utils.h"

int main(){
    std::string fileName = "../srt-files/";
    fileName.append("S01E01-Asteroids.srt");
    addOffset(fileName, 0, 0, 2, 0);
    return 0;
}

void addOffset(std::string subFile, int h, int m, int s, int ms){
    //TODO(if I decide to not be lazy): instead of creating a new file, and overwrite the old one

    std::string newName = subFile;
    newName.insert(newName.size()-4, "-edited");

    //open file from reading and new file for writing to
    std::ifstream oldFile(subFile);
    std::ofstream newFile(newName);
    
    std::string line;
    while(std::getline(oldFile, line)){
        int id;
        try{
            //TODO: find a better solution
            id = std::stoi(line);
            
            //if stoi succeeds, we know we have found a sub (with id id)
            newFile << id << '\n';          //save its id as normal
            std::getline(oldFile, line);    //get timestamp of the sub
            editTimestamp(line, h, m, s, ms);
            newFile << line;
        }
        catch(const std::invalid_argument &ia){
            //line does not start with a number,
            //write line as usual
            newFile << line;
        }
    }

    newFile.close();
    oldFile.close();
}

void editTimestamp(std::string &old, int h, int m, int s, int ms){
    std::stringstream ss;
    std::vector<std::string> times = splitString(old, ":, ");

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
                if(newTime < 10) //in order to write in the hh:mm:ss format
                    ss << 0;
                ss << newTime << delimiters[i];
            }
            int newTime = timeStamps[3] + offsets[3];
            if(newTime < 100)   //extra possible 0
                ss << 0;
            if(newTime < 10)
                ss << 0;
            ss << newTime;

            stampNum++;
        }
    }
    ss << '\n';
    
    old = ss.str();
}
