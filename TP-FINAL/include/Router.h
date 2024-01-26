#ifndef ROUTER_H
#define ROUTER_H

#include "Terminal.h"
#include "Lista.h"
#include "Paquete.h"

class Router
{
private:
    int id;
    Lista<Router *> *routers_vecinos;
    Lista<Terminal *> *terminales_conectados;

    // Lista<Pagina *> *paginas_enviadas;
    // Lista<Pagina *> *paginas_recibidas;

    Cola<Paquete *> *inPackets;
    Cola<Paquete *> *outPackets;

public:
    Router(int id)
    {
        this->id = id;
        routers_vecinos = new Lista<Router *>();
        terminales_conectados = new Lista<Terminal *>();
        inPackets = new Cola<Paquete *>();
        outPackets = new Cola<Paquete *>();
    };
    //~Router();
    void add_terminal(Terminal *t);
    void add_neighbors(Router *r);
    int getId() { return id; };
    // void setEnvio(Pagina *page) { paginas_enviadas->add(page); };
    Lista<Router *> *getNeighbors() { return routers_vecinos; };
    Lista<Terminal *> *getTerminals() { return terminales_conectados; };
    void receive_page(Pagina *p);
    void send_packet();
    Cola<Paquete *> *getInPackets() { return inPackets; };
    void receive_packet(Paquete *pkg);
    bool check_completion(Paquete *p);
    // void check_files(Cola<Paquete *> *aux);
};

#endif