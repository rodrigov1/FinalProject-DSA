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

/* Lector del archivo configuracion.txt */
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

/* Creador de routers */
void Administrador::crear_routers(int r)
{
    cant_routers += r;
    for (int i = 0; i < r; i++)
    {
        Router *router = new Router(i);
        routers_disponibles->addFinal(router);
    }
}

/* Conector de terminales a routers */
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

/* Imprime los router disponibles */
void Administrador::print_r()
{
    Nodo<Router *> *aux = routers_disponibles->get_czo();
    for (int i = 0; i < routers_disponibles->size(); i++)
    {
        cout << "Router: " << aux->get_dato()->getId() << endl;
        aux = aux->get_next();
    }
}

/* Imprime los terminales disponibles */
void Administrador::print_t()
{
    Nodo<Terminal *> *aux = terminales_disponibles->get_czo();
    for (int i = 0; i < terminales_disponibles->size(); i++)
    {
        cout << "Terminal: " << aux->get_dato()->getIP()[0] << ":" << aux->get_dato()->getIP()[1] << endl;
        aux = aux->get_next();
    }
}

/* Creates a new page and sends it to the appropriate terminal */
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

    if (origen != destino)
    {
        // cout << "Pagina " << pagina->getId() << "recibida " << endl;
        this->routers_disponibles->search_id(origen[0])->receive_page(pagina);
    }
    else
    {
        this->routers_disponibles->search_id(origen[0])->getTerminals()->search_id(origen[1])->recibir_pagina(pagina);
    }
}

/* Establece las conexiones en la red de routers */
void Administrador::establecer_conexion(int origen, int destino, int bw) 
{
    Router* aux1;
    Router* aux2;

    for(int i = 0; i < routers_disponibles->size(); i++) {
        if(i == origen) {
            aux1 = routers_disponibles->search_id(i);
        } else if(i == destino) {
            aux2 = routers_disponibles->search_id(i);
        }
    }

    Canal* c = new Canal(aux1,aux2,bw);
    canales->addFinal(c);
}
