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

/** Agrega una terminal a la lista del router 
 * @param t puntero tipo Terminal
*/
void Router::add_terminal(Terminal *t)
{
    terminales_conectados->addFinal(t);
    // t->add_router(this);
}

/** Agrega un router vecino a la lista del router
 * @param r puntero tipo Router
*/
void Router::add_neighbors(Router *r)
{
    routers_vecinos->addFinal(r);
}

/** Recibe una pagina y la separa en n paquetes 
 * @param p puntero tipo Pagina a separar
*/
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
        size_pak = 1;
    }

    // cout << "Cantidad de paquetes: " << n << " de tamaño: " << size_pak << endl;

    // Se crean n paquetes y se encolan todos en la cola de salida
    for (int j = 0; j < n; j++)
    {
        Paquete *aux = new Paquete(j, p, size_pak);
        // cout << "Pkg " << aux->getId() << " de tamaño " << aux->getSize() << " creado" << endl;
        outPackets->encolar(aux);
    }
    // delete p;        // borrado del objeto pagina
    print_packets(); // Imprime los paquetes que se van a enviar, solo para debuggear
}

/** Decide el destino del paquete recibido por el router 
 * @param pkg puntero tipo Paquete a decidir
*/
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

/** Recrea la pagina luego de juntar todos los paquetes necesarios 
 * @param pkg puntero tipo Paquete de muestra
*/
Pagina *Router::recreate_page(Paquete *pkg)
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

/** Comprueba si los paquetes que tienen de destino al router
 *  son todos los necesarios para crear la pagina correspondiente
 * @param pkg puntero tipo Paquete de muestra para chequear
*/
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

/* Envia el paquete al router vecino correspondiente */
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
        }
        else
        {
            for (int i = 0; i < this->getCanales()->size(); i++) // Busca si el destino es un vecino
            {
                if (this->getCanales()->search_id(i)->getDestino() == aux->get_dato()->getDestino()[0])
                {
                    this->getCanales()->search_id(i)->add_packet(aux->get_dato());
                    outPackets->desencolar();
                    vecino = true;
                    break;
                }
            }
            if (!vecino) // Si no es vecino, busca si hay una ruta disponible
            {
                if (this->getRutas()->size() == 0)
                {
                    cout << "No hay rutas disponibles" << endl;
                    return;
                }
                int canal_optimo = 0;
                int dist_actual = 0;
                int dist_optima = 9999; // Inicializa la distancia optima en un numero grande
                for (int i = 0; i < this->getRutas()->size(); i++)
                {
                    if (this->getRutas()->search_id(i)->getLast() == aux->get_dato()->getDestino()[0]) // Busca si hay una ruta disponible con el destino del paquete
                    {
                        for (int j = 0; j < this->getCanales()->size(); j++)
                        {
                            if (this->getCanales()->search_id(j)->getDestino() == this->getRutas()->search_id(i)->getNext()) // Busca si hay un canal disponible con el primer nodo de la ruta
                            {
                                dist_actual = this->getRutas()->search_id(i)->getDistancia();
                                canal_optimo = j;
                                break;
                            }
                        }
                    }
                    if (dist_actual < dist_optima) // Busca la ruta mas corta para el destino del paquete
                    {
                        dist_optima = dist_actual;
                    }
                }
                if (dist_optima != 9999)
                {
                    this->getCanales()->search_id(canal_optimo)->add_packet(aux->get_dato()); // Agrega el paquete al buffer del canal
                    outPackets->desencolar();
                    return;
                }
                else
                {
                    cout << "No hay ruta disponible para este paquete" << endl; // En caso de que no haya ruta disponible para el paquete
                }
            }
        }
    }
}

/** Retorna si un router es vecino o no 
 * @param id_r id del router a comprobar
*/
bool Router::es_vecino(int id_r)
{
    Nodo<Router *> *aux = routers_vecinos->get_czo();
    for (int i = 0; i < routers_vecinos->size(); i++)
    {
        if (aux->get_dato()->getId() == id_r)
        {
            return true;
        }
        aux = aux->get_next();
    }
    return false;
}