#ifndef SRT_EDITOR_SRC_OFFSETTER_H
#define SRT_EDITOR_SRC_OFFSETTER_H

#include <string>

void addOffset(std::string filename, int h, int m, int s, int ms);

void editTimestamp(std::string &old, int h, int m, int s, int ms);

#endif  /*  SRT_EDITOR_SRC_OFFSETTER_H  */