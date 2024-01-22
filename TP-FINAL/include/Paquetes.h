#ifndef PAQUETES_H
#define PAQUETES_H
#include "Pagina.h"

using namespace std;

class Paquetes
{
private:
    int id;
    Pagina *page;
    int indiceTotal;

public:
    Paquetes(int id, Pagina *page, int indiceTotal)
    {
        this->id = id;
        this->page = page;
        this->indiceTotal = indiceTotal;
    };
    ~Paquetes();
    void setId();
    int getId();
    void setPage();
    Pagina getPage();
};

#endif