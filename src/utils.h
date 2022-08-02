#ifndef SRT_EDITOR_SRC_UTILS_H
#define SRT_EDITOR_SRC_UTILS_H

#include <vector>

void printUsage();

bool isNewLine(std::string compare);

std::vector<std::string> splitString(std::string toSplit, std::string delimiters);

<<<<<<< Updated upstream
=======
std::string getOtherFile();

void removeLineEndings(std::string &toEdit);

>>>>>>> Stashed changes
#endif  /*  SRT_EDITOR_SRC_UTILS_H  */