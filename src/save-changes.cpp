#include <string>
#include <fstream>
#include <iostream>

#include "save-changes.h"

int saveChanges(std::string fileName){
    //TODO(if I decide to not be lazy): instead of creating a new file, backup the and edit the old one
    std::string backupName = fileName;
    backupName.insert(backupName.size()-4, "-edited");

    //open file for reading and new file for writing to
    std::ifstream backupFile(backupName);
    std::ofstream originalFile(fileName);

    std::string line;
    while(std::getline(backupFile, line)){
        line.append("\n");  //getline ignores \n
        originalFile << line;
    }

    originalFile.close();
    backupFile.close();

    if(std::remove(backupName.c_str()) != 0){
        std::cout << "Error deleting the backup file." << std::endl;
        return 1;
    }
    return 0;
}