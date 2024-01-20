#ifndef TERMINAL_H
#define TERMINAL_H

#include "Pagina.h"
#include "Lista.h"

class Terminal
{
private:
    int ip[2];
    Cola<Pagina *> *pages;

public:
    Terminal(){};
    Terminal(int a, int b)
    {
        ip[0] = a, ip[1] = b;
        pages = new Cola<Pagina *>();
    };
    //~Terminal();
    int *getIP() { return this->ip; };
    void recibir_pagina(Pagina *page);
    Cola<Pagina *> *getPages() { return pages; };
};

#endif