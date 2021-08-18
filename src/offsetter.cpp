#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>

#include "offsetter.h"
#include "utils.h"
// ./srt-editor + hh:mm:ss:msc file
// ./srt-editor + hh:mm:ss:msc hh:mm:ss:msc hh:mm:ss:msc file
int main(int argc, char *argv[]){
    if(argc != 4 && argc != 6){   //eventually I'll allow editing multiple files
        printUsage();
        return 1;
    }

    int offsets[4];
    int start[4];
    int end[4];
    std::string fileName = "";
    
    if(parseCommand(argc, argv, offsets, start, end, &fileName) != 0) return 1;

    addOffset(fileName, start, end, offsets[0], offsets[1], offsets[2], offsets[3]);

    return 0;
}

void addOffset(std::string subFile, int *start, int *end, int h, int m, int s, int ms){
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
            editTimestamp(line, start, end, h, m, s, ms);
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

            //TODO: move this check outside of this function?
            //only check if we can edit if the start value is between bounds
            if(i == 0) edit = canEdit(timestamps, start, end);
            
            //TODO: set up modular arithmetic
            int offsets[4] = {h, m, s, ms};
            char delimiters[3] = {':', ':', ','};

            for(size_t i = 0; i < 3; i++){
                int newTime = timestamps[i];
                if(edit) newTime += offsets[i];
                ss << std::setfill('0') << std::setw(2) << newTime << delimiters[i];
            }

            int newTime = timestamps[3];
            if(edit) newTime += offsets[3];
            ss << std::setfill('0') << std::setw(3) << newTime;

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

// void tests(){
//     int s1[4] = {0, 0, 0, 0};
//     int t1[4] = {0, 0, 0, 0};
//     int e1[4] = {59, 59, 59, 999};
    
//     int s2[4] = {0, 0, 0, 0};
//     int t2[4] = {0, 3, 31, 123};
//     int e2[4] = {59, 59, 59, 999};
    
//     int s3[4] = {1, 0, 0, 0};
//     int t3[4] = {2, 0, 0, 0};
//     int e3[4] = {4, 0, 0, 0};
    
//     int s4[4] = {1, 0, 0, 0};
//     int t4[4] = {1, 0, 0, 0};
//     int e4[4] = {4, 0, 0, 0};
    
//     int s5[4] = {1, 0, 0, 0};
//     int t5[4] = {4, 0, 0, 0};
//     int e5[4] = {4, 0, 0, 0};
    
//     int s6[4] = {2, 31, 10, 23};
//     int t6[4] = {2, 30, 23, 9};
//     int e6[4] = {4, 10, 10, 24};

//     int s7[4] = {0, 30, 0, 0};
//     int t7[4] = {1, 10, 0, 0};
//     int e7[4] = {1, 40, 0, 0};
    
//     int s8[4] = {0, 30, 30, 0};
//     int t8[4] = {1, 30, 10, 0};
//     int e8[4] = {1, 40, 40, 0};
    
//     int s9[4] = {0, 30, 30, 30};
//     int t9[4] = {1, 30, 30, 10};
//     int e9[4] = {1, 40, 40, 40};
    
//     int s10[4] = {1, 30, 24, 30};
//     int t10[4] = {1, 30, 24, 10};
//     int e10[4] = {4, 0, 0, 0};
    
//     int s11[4] = {1, 30, 24, 30};
//     int t11[4] = {1, 30, 24, 30};
//     int e11[4] = {4, 0, 0, 0};
    
//     int s12[4] = {1, 30, 24, 30};
//     int t12[4] = {1, 30, 23, 10};
//     int e12[4] = {4, 0, 0, 0};
    
//     int s13[4] = {0, 0, 25, 0};
//     int t13[4] = {0, 0, 30, 982};
//     int e13[4] = {0, 0, 30, 982};
    
//     int s14[4] = {0, 0, 25, 0};
//     int t14[4] = {0, 0, 30, 983};
//     int e14[4] = {0, 0, 30, 982};
    
//     std::cout << "t exp|res\n";
//     std::cout << "t1 " << true << " |" << canEdit(t1, s1, e1) << "\n";
//     std::cout << "t2 " << true << " |" << canEdit(t2, s2, e2) << "\n";
//     std::cout << "t3 " << true << " |" << canEdit(t3, s3, e3) << "\n";
//     std::cout << "t4 " << true << " |" << canEdit(t4, s4, e4) << "\n";
//     std::cout << "t5 " << true << " |" << canEdit(t5, s5, e5) << "\n";
//     std::cout << "t6 " << false << " |" << canEdit(t6, s6, e6) << "\n";
//     std::cout << "t7 " << true << " |" << canEdit(t7, s7, e7) << "\n";
//     std::cout << "t8 " << true << " |" << canEdit(t8, s8, e8) << "\n";
//     std::cout << "t9 " << true << " |" << canEdit(t9, s9, e9) << "\n";
//     std::cout << "t10 " << false << " |" << canEdit(t10, s10, e10) << "\n";
//     std::cout << "t11 " << true << " |" << canEdit(t11, s11, e11) << "\n";
//     std::cout << "t12 " << false << " |" << canEdit(t12, s12, e12) << "\n";
//     std::cout << "t13 " << true << " |" << canEdit(t13, s13, e13) << "\n";
//     std::cout << "t14 " << false << " |" << canEdit(t14, s14, e14) << "\n";
// }
