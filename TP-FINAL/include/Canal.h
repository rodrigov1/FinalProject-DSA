#ifndef CANAL_H
#define CANAL_H

#include "Lista.h"
#include "Router.h"
#define INFI 9999

class Canal {
private:
    Router *origen;
    Router *destino;
    int bw;
    int peso = INFI;

public:
    Canal(Router *origen, Router *destino, int bw)
    {
        this->origen = origen;
        this->destino = destino;
        this->bw = bw;
        peso = 1;
    };
    ~Canal();
    int getOrigen() { return origen; };
    int getDestino() { return destino; };
    int getBw() { return bw; };
    int getPeso() { return peso; };
};

#endif