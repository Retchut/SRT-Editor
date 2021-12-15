#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>

#include "offsetter.h"
#include "utils.h"

void addOffset(std::string subFile){

    //TODO(if I decide to not be lazy): instead of creating a new file, backup the and edit the old one
    std::string newName = subFile;
    newName.insert(newName.size()-4, "-edited");

    //open file from reading and new file for writing to
    std::ifstream oldFile(subFile);
    std::ofstream newFile(newName);

    int offsets[4];
    int start[4];
    int end[4];
    while(true){
        if(getOffsets(offsets, start, end) == 0) break;
    }

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
            editTimestamp(line, start, end, offsets[0], offsets[1], offsets[2], offsets[3]);
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

void editTimestamp(std::string &old, int *start, int *end, int h, int m, int s, int ms){
    std::stringstream ss;
    std::vector<std::string> times = splitString(old, ":, ");    

    ss << std::setfill('0') << std::setw(5);

    int stampNum = 0;
    bool edit = true;
    for(size_t i = 0; i < 3; i++){
        if(i == 1){    //arrow
            ss << " " << times[4] << " ";
        }
        else{
            //TODO: clean up this mess, god it hurts my eyes
            int timestamps[4] = {
                std::stoi(times[stampNum*5+0]), std::stoi(times[stampNum*5+1]),
                    std::stoi(times[stampNum*5+2]), std::stoi(times[stampNum*5+3])        
                                };
            
            int offsets[4] = {h, m, s, ms};
            char delimiters[3] = {':', ':', ','};

            //TODO: move this check outside of this function?
            //only check if we can edit if the start value is between bounds
            if(i == 0) edit = canEdit(timestamps, start, end);
            
            //calculate
            //TODO: Clean this mess up
            if(edit){
                int carryOver = 0;
                timestamps[3] += offsets[3];
                if(timestamps[3] / 1000 > 0){
                    carryOver = (timestamps[3] / 1000);
                    timestamps[3] -= 1000 * carryOver;
                }
                else if(timestamps[3] < 0){
                    carryOver = (timestamps[3] / 1000) - 1;
                    timestamps[3] += ((timestamps[3] / 1000) - 1) * - 1000;
                }

                for(int i = 2; i >= 0; i--){
                    timestamps[i] += (offsets[i] + carryOver);
                    if((timestamps[i] / 60 > 0) && (i != 0)){
                        carryOver = (timestamps[i] / 60);
                        timestamps[i] -= 60 * carryOver;
                    }
                    else if(timestamps[i] < 0){
                        carryOver = (timestamps[i] / 60) - 1;
                        timestamps[i] += ((timestamps[i] / 60) - 1) * - 60;
                    }
                    else{
                        carryOver = 0;
                    }
                }
            }

            //write to file
            for(size_t i = 0; i < 3; i++){
                ss << std::setfill('0') << std::setw(2) << timestamps[i] << delimiters[i];
            }
            ss << std::setfill('0') << std::setw(3) << timestamps[3];

            stampNum++;
        }
    }
    ss << "\n";
    
    old = ss.str();
}

bool canEdit(int *timestamps, int *start, int *end){
    //TODO: clean up this ugly mess
    if(timestamps[0] < start[0] || timestamps[0] > end[0]) return false;
    
    if(timestamps[0] == start[0]){
        if(timestamps[1] < start[1]) return false;
        else if(timestamps[1] == start[1]){
            if(timestamps[2] < start[2]) return false;
            else if(timestamps[2] == start[2]){
                if(timestamps[3] < start[3]) return false;
                else return true;
            }
        }
    }
    
    if(timestamps[0] == end[0]){
        if(timestamps[1] > end[1]) return false;
        else if(timestamps[1] == end[1]){
            if(timestamps[2] > end[2]) return false;
            else if(timestamps[2] == end[2]){
                if(timestamps[3] > end[3]) return false;
                else return true;
            }
        }
    }
    
    return true;
}