#include "../include/Terminal.h"
#include <iostream>
#include <string>

using namespace std;

Terminal::Terminal(int d[2])
{
    this->ip[0] = d[0];
    this->ip[1] = d[1];
}