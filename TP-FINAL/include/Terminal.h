#ifndef TERMINAL_H
#define TERMINAL_H

class Terminal
{
private:
    int ip[2];

public:
    Terminal(){};
    Terminal(int[2]);
    int *getIP() { return this->ip; };
};

#endif