#ifndef ROUTER_H
#define POUTER_H

#include <string>
#include "Cola.h"
#include "Paquetes.h"
#include "Pagina.h"

using namespace std;

class Router {
private:
    int id;
    int terminal;
    Cola<Paquetes*> incomingPackages;
    Cola<Paquetes*> outgoingPackages;

public:
    Router(int id, int terminal) {
        this->id = id; 
        this->terminal = terminal;
        };
    //~Router();
    void setId();
    int getId();
    Cola<Paquetes*> dividePage(Pagina page);
};

#endif