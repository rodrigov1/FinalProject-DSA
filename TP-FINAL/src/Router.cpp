#include <iostream>
#include <string>
#include "../include/Router.h"
#include "../include/Lista.h"
#include "../include/Pagina.h"
#include "../include/Terminal.h"
#include "../include/Paquete.h"

using namespace std;

void Router::add_terminal(Terminal *t)
{
    terminales_conectados->addFinal(t);
    // t->add_router(this);
}

void Router::add_neighbors(Router *r)
{
    routers_vecinos->addFinal(r);
}

void Router::receive_page(Pagina *p)
{
    int n = 1;
    int size = 0;
    for (int i = 2; i < p->getSize(); i++)
    {
        if (p->getSize() % i == 0)
        {
            n = i;
            size = p->getSize() / i;
        }
    }

    if (n == 1)
    {
        n = p->getSize();
        size = 1;
        // cout << "El numero de paquetes es: " << p->getSize() << endl;
    }

    // cout << "Cantidad de paquetes: " << n << " de tamaño: " << size << endl;
    // Se crean n paquetes y se encolan todos en la cola de salida
    for (int j = 0; j < n; j++)
    {
        Paquete *aux = new Paquete(j, p, size);
        // cout << "Pkg " << aux->getId() << " de tamaño " << aux->getSize() << " creado" << endl;
        outPackets->encolar(aux);
    }

    delete p; // borrado del objeto pagina
}

void Router::receive_packet(Paquete *pkg)
{
    // cout << "El paquete " << pkg->getId() << " llego al router " << this->getId() << endl;
    if (pkg->getDestino()[0] == this->getId())
    {
        inPackets->encolar(pkg);
        if (check_completion(pkg))
        {
            Pagina *p = pkg->getPage();
            p->setArrived();
            this->getTerminals()->search_id(pkg->getDestino()[1])->recibir_pagina(p);
        }
    }
    else
    {
        outPackets->encolar(pkg);
    }
}

bool Router::check_completion(Paquete *pkg)
{
    Pagina *page = pkg->getPage();
    int cant = 0;
    Nodo<Paquete *> *aux = this->getInPackets()->get_czo();

    for (int i = 0; i < this->getInPackets()->sizeCola(); i++)
    {
        if (aux->get_dato()->getPage()->getId() == page->getId())
        {
            cant++;
        }
        aux = aux->get_next();
    }

    int size = cant * pkg->getSize();

    if (size == page->getSize())
    {
        return true;
    }
    return false;
}