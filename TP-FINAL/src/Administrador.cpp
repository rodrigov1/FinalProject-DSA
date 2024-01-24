#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include "../include/Lista.h"
#include "../include/Router.h"
#include "../include/Pagina.h"
#include "../include/Terminal.h"
#include "../include/Administrador.h"

using namespace std;

void Administrador::leer_config()
{
    srand(time(0)); // Seed the random number generator with the current time
    ifstream config_file("config.txt");
    string line;
    int num_routers, num_terminals;
    // Skip the first line
    getline(config_file, line);

    // Read the number of routers
    config_file >> num_routers;

    // Skips the next line
    getline(config_file, line);
    getline(config_file, line);

    config_file >> num_terminals;

    crear_routers(num_routers);         // crea los routers
    conectar_terminales(num_terminals); // llama al conector de terminales a routers
    /*int origen, destino, ancho;
    config_file >> origen;
    while (!config_file.eof()) // mientras no sea el final del archivo
    {
        config_file >> destino;
        config_file >> ancho;
        // establecer_conexion(origen, destino, ancho);
        config_file >> origen; // lee el siguiente origen
    }
    */
    config_file.close();
}

void Administrador::crear_routers(int c)
{
    cant_routers += c;
    for (int i = 0; i < c; i++)
    {
        Router *router = new Router(i);
        routers_disponibles->addFinal(router);
    }
}

/*                                   Conector de terminales a routers           */
void Administrador::conectar_terminales(int t)
{
    cant_terminals += t;
    Nodo<Router *> *aux = routers_disponibles->get_czo();

    for (int i = 0; i < cant_routers; i++)
    {
        // Creo la cantidad "t" de terminales para cada router
        for (int j = 0; j < t; j++)
        {
            Terminal *te = new Terminal(i, j);
            aux->get_dato()->add_terminal(te);
            terminales_disponibles->addFinal(te); // Lista de todos los terminales que ve el administrador
        }
        aux = aux->get_next(); // Paso al siguiente router de la lista
    }
}

void Administrador::print_r()
{
    Nodo<Router *> *aux = routers_disponibles->get_czo();
    for (int i = 0; i < routers_disponibles->size(); i++)
    {
        cout << "Router: " << aux->get_dato()->getId() << endl;
        aux = aux->get_next();
    }
}

void Administrador::print_t()
{
    Nodo<Terminal *> *aux = terminales_disponibles->get_czo();
    for (int i = 0; i < terminales_disponibles->size(); i++)
    {
        cout << "Terminal: " << aux->get_dato()->getIP()[0] << ":" << aux->get_dato()->getIP()[1] << endl;
        aux = aux->get_next();
    }
}

/**
 * Creates a new page and sends it to the appropriate terminal.
 */
void Administrador::crear_pagina()
{
    int origen_r = rand() % cant_routers;
    int origen_t = rand() % cant_terminals;
    int origen[2] = {origen_r, origen_t};
    int destino_r = rand() % cant_routers;
    int destino_t = rand() % cant_terminals;
    int destino[2] = {destino_r, destino_t};
    int size = rand() % 100;
    Pagina *pagina = new Pagina(id_paginas, size, origen, destino);
    // cout << "Pagina creada: " << pagina->getId() << " de tamaño " << pagina->getSize() << endl;
    id_paginas++;

    Nodo<Router *> *aux2 = this->routers_disponibles->get_czo();

    for (int i = 0; i < this->routers_disponibles->size(); i++) // Recorre la lista de router hasta encontrar el router origen
    {
        if (pagina->getOrigin()[0] == aux2->get_dato()->getId())
        {
            Nodo<Terminal *> *aux = aux2->get_dato()->getTerminals()->get_czo();
            while (aux->get_dato()->getIP()[1] != pagina->getOrigin()[1]) // Recorre la lista de terminales hasta encontrar el terminal origen
            {
                aux = aux->get_next();
            }
            if (pagina->getOrigin() != pagina->getDest())
            {
                // cout << "Pagina " << pagina->getId() << "recibida " << endl;
                aux2->get_dato()->divide_page(pagina);
            }
            else
            {
                pagina->setArrived();
                aux->get_dato()->recibir_pagina(pagina);
            }
        }
        aux2 = aux2->get_next();
    }
}
