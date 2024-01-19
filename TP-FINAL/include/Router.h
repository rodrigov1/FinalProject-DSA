#ifndef ROUTER_H
#define ROUTER_H

#include "Lista.h"
#include "Terminal.h"

class Router
{
private:
    int id;
    int terminal;
    Lista<Router *> *routers_vecinos;
    Lista<Terminal *> *terminals_conectados;

    // Cola<Packages *> incomingPackages;
    // Cola<Packages *> outgoingPackages;

public:
    Router(){};
    Router(int id)
    {
        this->id = id;
        routers_vecinos = new Lista<Router *>();
        terminals_conectados = new Lista<Terminal *>();
    }
    void add_terminal(Terminal *t);
    //~Router();
};

#endif