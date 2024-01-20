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
    Lista<Pagina*> *paginas_enviadas;
    Lista<Pagina*> *paginas_recibidas;

    Cola<Paquetes*> incomingPackages;
    Cola<Paquetes*> outgoingPackages;

public:
    Router(int id) {
        this->id = id;
        routers_vecinos = new Lista<Router *>();
        terminales_conectados = new Lista<Terminal *>();
    };
    //~Router();
    void add_terminal(Terminal *t);
    void add_neighbors(Router *r);
    int getId() { return id; };
    void setEnvio(Pagina* page) { paginas_enviadas->add(page); };
    Lista<Router*>* getNeighbors() {return routers_vecinos; };
};

#endif