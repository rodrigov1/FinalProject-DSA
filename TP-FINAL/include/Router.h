#ifndef ROUTER_H
#define ROUTER_H

#include "Lista.h"
#include "Terminal.h"
#include "Paquetes.h"

class Router {
private:
    int id;
    Lista<Router*> *routers_vecinos;
    Lista<Terminal*> *terminales_conectados;

    Cola<Paquetes *> incomingPackages;
    Cola<Paquetes *> outgoingPackages;

public:
    Router(int id) {
        this->id = id;
        routers_vecinos = new Lista<Router *>();
        terminales_conectados = new Lista<Terminal *>();
    };
    //~Router();
    void add_terminal(Terminal *t);
    int getId() { return id; };
};

#endif