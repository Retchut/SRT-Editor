#ifndef SRT_EDITOR_SRC_UTILS_H
#define SRT_EDITOR_SRC_UTILS_H

#include <vector>
#include <string>

void printUsage();

unsigned int cli();

void printMenu();

int getOffsets(int *start, int *end, int *offsets);

bool isNewLine(std::string compare);

std::vector<std::string> splitString(std::string toSplit, std::string delimiters);

#endif  /*  SRT_EDITOR_SRC_UTILS_H  */