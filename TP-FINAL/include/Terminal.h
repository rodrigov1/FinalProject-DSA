#ifndef TERMINAL_H
#define TERMINAL_H

class Terminal {
private:
    int ip[2];

public:
    Terminal(){};
    Terminal(int a, int b) { 
        ip[0] = a, ip[1] = b; 
    };
    int *getIP() { return this->ip; };
};

#endif