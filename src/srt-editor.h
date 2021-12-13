#ifndef _SRT_EDITOR_H_
#define _SRT_EDITOR_H_

#include <string>

void checkIDs(std::string subFile);

void addOffset(std::string subFile);

void editTimestamp(std::string &old, int *start, int *end, int h, int m, int s, int ms);

bool canEdit(int *timestamps, int *start, int *end);

// void tests();

#endif  /*  _SRT_EDITOR_H_  */