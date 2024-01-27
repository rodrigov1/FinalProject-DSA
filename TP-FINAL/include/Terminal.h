#ifndef TERMINAL_H
#define TERMINAL_H

// #include "Router.h"
#include "Pagina.h"
#include "Lista.h"

class Terminal
{
private:
    int ip[2];
    // Router *router_conectado;
    Cola<Pagina *> *pages;

public:
    Terminal(int a, int b)
    {
        ip[0] = a, ip[1] = b;
        pages = new Cola<Pagina *>();
    };
    ~Terminal();
    // void add_router(Router *r) { router_conectado = r; };
    int *getIP() { return this->ip; };
    void recibir_pagina(Pagina *page);
    Cola<Pagina *> *getPages() { return pages; };
};

#endif