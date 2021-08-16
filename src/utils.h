#ifndef SRT_EDITOR_SRC_UTILS_H
#define SRT_EDITOR_SRC_UTILS_H

#include <vector>
#include <string>

void printUsage();

int parseCommand(char *argv[], int *offsets, int *startInt, int *endInt, std::string *fileName);

bool isNewLine(std::string compare);

std::vector<std::string> splitString(std::string toSplit, std::string delimiters);

#endif  /*  SRT_EDITOR_SRC_UTILS_H  */