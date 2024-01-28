#ifndef CANAL_H
#define CANAL_H

#include "Lista.h"
// #include "Router.h"
#define INFI 9999

class Canal
{
private:
    int origen;
    int destino;
    int bw;
    int peso = INFI;

public:
    Canal(int orig, int dest, int bw)
    {
        this->origen = orig;
        this->destino = dest;
        this->bw = bw;
    };
    ~Canal();
    int getOrigen() { return origen; };
    int getDestino() { return destino; };
    int getBw() { return bw; };
    int getPeso() { return peso; };
    void send_package();
};

#endif