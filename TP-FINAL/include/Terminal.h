#ifndef TERMINAL_H
#define TERMINAL_H

#include "Pagina.h"
#include "Router.h"

class Terminal
{
private:
    int ip[2];

public:
    Terminal(){};
    Terminal(int a, int b)
    {
        ip[0] = a, ip[1] = b;
    };
    //~Terminal();
    int *getIP() { return this->ip; };
    void sendPage(int dest[2]);
};

#endif