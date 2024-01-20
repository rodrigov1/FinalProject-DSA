#ifndef CANAL_H
#define CANAL_H

#include "Lista.h"

class Canal
{
private:
    int origen;
    int destino;
    int bw;
    int peso;

public:
    Canal(int origen, int destino, int bw)
    {
        this->origen = origen;
        this->destino = destino;
        this->bw = bw;
    };
    ~Canal();
    int getOrigen() { return origen; };
    int getDestino() { return destino; };
    int getBw() { return bw; };
    // int getPeso() { return peso; };
};

#endif