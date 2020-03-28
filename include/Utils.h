//
// Created by wang on 2020/3/27.
//

#ifndef CHARTSTART_SERVER_UTILS_H
#define CHARTSTART_SERVER_UTILS_H
#include <string>
#include <vector>
#include "Common.h"
using std::vector;
using std::string;

string ch_string(char temp[Max_Buffer]);
vector<string> split(string src, char flag);
#endif //CHARTSTART_SERVER_UTILS_H

