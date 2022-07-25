#include <string>
#include <fstream>
#include <sstream>

#include "check-id.h"
#include "utils.h"

void checkIDs(std::string subFile){
    //TODO(if I decide to not be lazy): instead of creating a new file, backup the and edit the old one
    std::string newName = subFile;
    newName.insert(newName.size()-4, "-edited");

    //open file for reading and new file for writing to
    std::ifstream oldFile(subFile);
    std::ofstream newFile(newName);

    std::string line;

    unsigned int expectedID = 1;
    while(std::getline(oldFile, line)){
        line.append("\n");  //getline ignores \n
        if(isNewLine(line)){
            newFile << line;
        }
        else{
            //verify id line
            std::stringstream ss(line);
            unsigned int subID = 0;
            ss >> subID;
            if(subID != expectedID){
                newFile << expectedID << "\n";
            }
            else{
                newFile << line;
            }
            expectedID++;

            //treat timestamp line
            std::getline(oldFile, line);
            newFile << line << "\n";

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