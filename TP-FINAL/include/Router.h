#ifndef ROUTER_H
#define ROUTER_H

class Router
{
private:
    int id;
    int terminal;
    Lista<Router *> routers_vecinos;
    Lista<Terminal *> terminals_conectados;

    // Cola<Packages *> incomingPackages;
    // Cola<Packages *> outgoingPackages;

public:
    Router(){};
    Router(int id)
    {
        this->id = id;
    }
    void add_terminal(Terminal *t);
    //~Router();
};

#endif