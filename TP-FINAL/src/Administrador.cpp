#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include "../include/Lista.h"
#include "../include/Router.h"
#include "../include/Pagina.h"
#include "../include/Terminal.h"
#include "../include/Administrador.h"
#include "../include/Canal.h"

#define INFI 9999
#define MAX_NODOS 10
int TABLA_RUTEO[MAX_NODOS][MAX_NODOS];
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

    // Skip the next line
    getline(config_file, line);
    getline(config_file, line);

    int origen, destino, bw;
    config_file >> origen;

    while (!config_file.eof())
    {
        config_file >> destino;
        config_file >> bw;
        establecer_conexion(origen, destino, bw);
        config_file >> origen;
    }
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

/* Establece las conexiones de la red de routers */
void Administrador::establecer_conexion(int origen, int destino, int bw)
{
    Canal *c = new Canal(origen, destino, bw);
    routers_disponibles->search_id(origen)->getCanales()->addFinal(c);
    routers_disponibles->search_id(origen)->add_neighbors(routers_disponibles->search_id(destino));
    canales_totales->addFinal(c);
}

/* Ejecuta el envio sistemico de paquetes */
void Administrador::send_packets()
{
    Nodo<Router *> *aux = routers_disponibles->get_czo();
    for (int i = 0; i < routers_disponibles->size(); i++)
    {
        aux->get_dato()->send_packet();
        aux->get_dato()->print_packets();
        aux = aux->get_next();
    }
}

/**
 * Initializes the network by calculating the weights of the routers' connections.
 * The weight represents the cost or distance between routers in the network.
 *
 * @param source The index of the source router.
 */
void Administrador::initialize_network(int source)
{
    int peso[cant_routers];
    int aux = 0;

    for (int i = 0; i < routers_disponibles->size(); i++) // Inicializa el arreglo de pesos
    {
        Router *router_actual = routers_disponibles->search_id(i);
        if (i == source) // Analisis de peso para el router origen
        {
            peso[source] = 0;
        }
        else if (routers_disponibles->search_id(source)->es_vecino(i)) // Analisis de peso para los vecinos del router origen
        {
            for (int j = 0; j < router_actual->getCanales()->size(); j++)
            {
                Canal *canal_actual = router_actual->getCanales()->search_id(j);
                if (canal_actual->getOrigen() == source && canal_actual->getDestino() == i)
                {
                    canal_actual->calcular_peso();
                    aux = canal_actual->getPeso();
                }
                else
                {
                    aux = INFI;
                }
            }
        }
        else
        {
            aux = INFI;
        }
        peso[i] = aux; // Asigna el peso al arreglo
    }

    for (int i = 0; i < cant_routers; i++)
    {
        TABLA_RUTEO[source][i] = peso[i];
    }
}