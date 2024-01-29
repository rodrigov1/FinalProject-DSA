#ifndef CANAL_H
#define CANAL_H

#include "Lista.h"
// #include "Router.h"
#include "Paquete.h"
#define INFI 9999

class Canal {
private:
    int origen;
    int destino;
    int bw;
    int peso = INFI;
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
    int getPeso() { return peso; };
    void calcular_peso() { peso = buffer->size() / bw; }
    void add_packet(Paquete *p); // Agrega un paquete al buffer
    // Paquete *transmit_packet();  // Transmite un paquete random del buffer
    void print_buffer();
};

#endif