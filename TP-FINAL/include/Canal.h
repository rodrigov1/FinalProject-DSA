#ifndef CANAL_H
#define CANAL_H

#include "Lista.h"
// #include "Router.h"
#include "Paquete.h"

class Canal
{
private:
    int origen;
    int destino;
    int bw;
    int peso;
    Lista<Paquete *> *buffer;

public:
    Canal(int orig, int dest, int bw)
    {
        this->origen = orig;
        this->destino = dest;
        this->bw = bw;
        buffer = new Lista<Paquete *>();
    };
    ~Canal();
    int getOrigen() { return origen; };
    int getDestino() { return destino; };
    int getBw() { return bw; };
    int getPeso() { calcular_peso(); return peso; };
    void calcular_peso();
    void add_packet(Paquete *p); // Agrega un paquete al buffer
    Paquete *transmit_packet();  // Transmite un paquete random del buffer
    Lista<Paquete *> *getBuffer() { return buffer; };
    void print_buffer();
};

#endif