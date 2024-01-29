#include <iostream>
#include <string>
#include "../include/Router.h"
#include "../include/Lista.h"
#include "../include/Pagina.h"
#include "../include/Terminal.h"
#include "../include/Paquete.h"

#define GREEN "\x1b[32m"
#define RESET_COLOR "\x1b[0m"

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
    int size_pak = 0;
    int size_pag = p->getSize();

    // Busqueda del minimo comun multiplo
    for (int i = 2; i < size_pag; i++)
    {
        if (size_pag % i == 0)
        {
            n = i;
            size_pak = size_pag / i;
        }
    }
    // (en caso de ser numero primo)
    if (n == 1)
    {
        n = p->getSize();
        size = 1;
    }

    // cout << "Cantidad de paquetes: " << n << " de tamaño: " << size_pak << endl;
    
    // Se crean n paquetes y se encolan todos en la cola de salida
    for (int j = 0; j < n; j++)
    {
        Paquete *aux = new Paquete(j, p, size_pak);
        // cout << "Pkg " << aux->getId() << " de tamaño " << aux->getSize() << " creado" << endl;
        outPackets->encolar(aux);
    }
    delete p;        // borrado del objeto pagina
    print_packets(); // Imprime los paquetes que se van a enviar, solo para debuggear

}

void Router::receive_packet(Paquete *pkg)
{
    // cout << "El paquete " << pkg->getId() << " llego al router " << this->getId() << endl;
    if (pkg->getDestino()[0] == this->getId())
    {
        inPackets->encolar(pkg);
        if (check_completion(pkg))
        {
            int destino_t = pkg->getDestino()[1];
            Pagina *page = recreate_page(pkg);
            terminales_conectados->search_id(destino_t)->recibir_pagina(page);
        }
    } else {
        outPackets->encolar(pkg);
    }
}

Pagina* Router::recreate_page(Paquete *pkg)
{
    Pagina *page = pkg->getPage();
    Nodo<Paquete *> *aux = this->getInPackets()->get_czo();
    for (int i = 0; i < this->getInPackets()->sizeCola(); i++)
    {
        if (aux->get_dato()->getPage()->getId() == page->getId())
        {
            this->getInPackets()->desencolar();
        }
        aux = aux->get_next();
    }
    page->setArrived();
    return page;
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

/* Prints packets to be send */
void Router::print_packets()
{
    cout << GREEN << "Paquetes del Router " << this->getId() << RESET_COLOR << endl;
    cout << "Num_paquete | Origen | Destino | Id_Pagina" << endl;
    Nodo<Paquete *> *aux = outPackets->get_czo();
    for (int i = 0; i < outPackets->size(); i++)
    {
        cout << aux->get_dato()->getId() << "              " << aux->get_dato()->getOrigen()[0] << ":" << aux->get_dato()->getOrigen()[1]
             << "       " << aux->get_dato()->getDestino()[0] << ":" << aux->get_dato()->getDestino()[1] << "        " << aux->get_dato()->getPage()->getId() << endl;
        aux = aux->get_next();
    }
    cout << endl;
}

void Router::send_packet()
{
    bool vecino = false;
    if (!outPackets->colavacia())
    {
        Nodo<Paquete *> *aux = outPackets->get_czo();
        if (this->getCanales()->size() == 0)
        {
            cout << "No hay canales disponibles" << endl;
            return;
        }
        if (aux->get_dato()->getDestino()[0] == this->getId())
        {
            receive_packet(aux->get_dato());
            outPackets->desencolar();
            return;
        } else {
            for (int i = 0; i < this->getCanales()->size(); i++)
            {
                if (this->getCanales()->search_id(i)->getDestino() == aux->get_dato()->getDestino()[0])
                {
                    this->getCanales()->search_id(i)->add_packet(aux->get_dato());
                    outPackets->desencolar();
                    vecino = true;
                    break;
                }
            }
            if (!vecino)
            {
                cout << "No hay conexion directa con el router " << aux->get_dato()->getDestino()[0] << endl;
                return;
            }
        }
    }
}