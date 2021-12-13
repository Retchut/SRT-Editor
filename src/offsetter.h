#ifndef SRT_EDITOR_SRC_OFFSETTER_H
#define SRT_EDITOR_SRC_OFFSETTER_H

#include <string>

void addOffset(std::string filename, int *start, int *end, int h, int m, int s, int ms);

void editTimestamp(std::string &old, int *start, int *end, int h, int m, int s, int ms);

bool canEdit(int *timestamps, int *start, int *end);

// void tests();

#endif  /*  SRT_EDITOR_SRC_OFFSETTER_H  */