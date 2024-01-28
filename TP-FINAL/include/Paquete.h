#ifndef PAQUETE_H
#define PAQUETE_H
#include "Pagina.h"

using namespace std;

class Paquete
{
private:
    int id;
    Pagina *page;
    int origen[2];
    int destino[2];
    int size_pkg;

public:
    Paquete(int id, Pagina *page, int size_pkg)
    {
        this->id = id;
        this->page = page;
        this->origen[0] = page->getOrigin()[0];
        this->origen[1] = page->getOrigin()[1];
        this->destino[0] = page->getDest()[0];
        this->destino[1] = page->getDest()[1];
        this->size_pkg = size_pkg;
    };
    //~Paquete();
    void setId();
    int getSize() { return size_pkg; };
    int getId() { return id; };
    int *getOrigen() { return origen; };
    int *getDestino() { return destino; };
    Pagina *getPage() { return page; };
};

#endif