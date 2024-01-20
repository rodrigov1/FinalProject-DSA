#ifndef PAQUETES_H
#define PAQUETES_H
#include "Pagina.h"

using namespace std;

class Paquetes
{
private:
    int id;
    Pagina page;

public:
    Paquetes(int id, Pagina page)
    {
        this->id = id;
        this->page = page;
    };
    ~Paquetes();
    void setId();
    int getId();
    void setPage();
    Pagina getPage();
};

#endif