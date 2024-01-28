#ifndef ROUTER_H
#define ROUTER_H

#include "Terminal.h"
#include "Lista.h"
#include "Paquete.h"
#include "Canal.h"

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
    Lista<Canal *> *canales_ida;

public:
    Router(int id)
    {
        this->id = id;
        routers_vecinos = new Lista<Router *>();
        canales_ida = new Lista<Canal *>();
        terminales_conectados = new Lista<Terminal *>();
        inPackets = new Cola<Paquete *>();
        outPackets = new Cola<Paquete *>();
    };
    ~Router();
    void add_terminal(Terminal *t);
    void add_neighbors(Router *r);
    int getId() { return id; };
    // void setEnvio(Pagina *page) { paginas_enviadas->add(page); };
    // Lista<Router *> *getNeighbors() { return routers_vecinos; };
    Lista<Terminal *> *getTerminals() { return terminales_conectados; };
    Lista<Router *> *getNeighbors() { return routers_vecinos; };
    void receive_page(Pagina *p);
    void send_packet();
    Cola<Paquete *> *getInPackets() { return inPackets; };
    Lista<Canal *> *getCanales() { return canales_ida; };
    void receive_packet(Paquete *pkg);
    bool check_completion(Paquete *p);
    void print_packets();
    Pagina *recreate_page(Paquete *p);
    // void check_files(Cola<Paquete *> *aux);
};

#endif