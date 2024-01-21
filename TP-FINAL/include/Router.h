#ifndef ROUTER_H
#define ROUTER_H

#include "Terminal.h"
#include "Lista.h"
#include "Paquetes.h"

class Router
{
private:
    int id;
    Lista<Router *> *routers_vecinos;
    Lista<Terminal *> *terminales_conectados;

    // Lista<Pagina *> *paginas_enviadas;
    // Lista<Pagina *> *paginas_recibidas;

    Cola<Paquetes *> inPackets;
    Cola<Paquetes *> outPackets;

public:
    Router(int id)
    {
        this->id = id;
        routers_vecinos = new Lista<Router *>();
        terminales_conectados = new Lista<Terminal *>();
    };
    //~Router();
    void add_terminal(Terminal *t);
    void add_neighbors(Router *r);
    int getId() { return id; };
    // void setEnvio(Pagina *page) { paginas_enviadas->add(page); };
    Lista<Router *> *getNeighbors() { return routers_vecinos; };
    Lista<Terminal *> *getTerminals() { return terminales_conectados; };
    void divide_page(Pagina *p);
};

#endif