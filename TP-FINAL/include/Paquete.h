#ifndef PAQUETE_H
#define PAQUETE_H
#include "Pagina.h"

using namespace std;

class Paquete
{
private:
    int id;
    int page_id;
    int origen[2];
    int destino[2];
    int size_pkg;
    int size_pag;

public:
    Paquete(int id, int origen[], int destino[], int page_id, int size_pkg, int size_pag)
    {
        this->id = id;
        this->origen[0] = origen[0];
        this->origen[1] = origen[1];
        this->destino[0] = destino[0];
        this->destino[1] = destino[1];
        this->page_id = page_id;
        this->size_pkg = size_pkg;
        this->size_pag = size_pag;
    };
    //~Paquete();
    void setId();
    int getSize() { return size_pkg; };
    int getId() { return id; };
    int *getOrigen() { return origen; };
    int *getDestino() { return destino; };
    int getPageId() { return page_id; };
    int getSizePag() { return size_pag; };
};

#endif