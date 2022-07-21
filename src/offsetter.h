#ifndef _OFFSETTER_H_
#define _OFFSETTER_H_

#include <string>

void addOffset(std::string subFile);

int getOffsets(int *start, int *end, int *offsets);

void editTimestamp(std::string &old, int *start, int *end, int h, int m, int s, int ms);

bool canEdit(int *timestamps, int *start, int *end);

#endif  /*  _OFFSETTER_H_  */