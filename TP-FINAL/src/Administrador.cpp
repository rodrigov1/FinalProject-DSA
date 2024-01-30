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
#define BLUE "\033[36;1m"
#define RESET_COLOR "\x1b[0m"

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
    int aux = -1;

    for (int i = 0; i < routers_disponibles->size(); i++) // Inicializa el arreglo de pesos
    {
        if (i == source) // Analisis de peso para el router origen
        {
            peso[source] = 0;
        }
        else if (routers_disponibles->search_id(source)->es_vecino(i)) // Analisis de peso para los vecinos del router origen
        {
            for (int j = 0; j < canales_totales->size(); j++)
            {
                if (canales_totales->search_id(j)->getOrigen() == source && canales_totales->search_id(j)->getDestino() == i)
                {
                    canales_totales->search_id(j)->calcular_peso();
                    aux = canales_totales->search_id(j)->getPeso();
                    cout << "Peso del canal " << canales_totales->search_id(j)->getOrigen() << " a " << canales_totales->search_id(j)->getDestino() << " es " << canales_totales->search_id(j)->getPeso() << endl;
                }
            }
            peso[i] = aux;
        }
        else
        {

            peso[i] = INFI;
        }
    }

    for (int i = 0; i < cant_routers; i++)
    {
        TABLA_RUTEO[source][i] = peso[i];
    }
}
void Administrador::print_network()
{
    for (int i = 0; i < routers_disponibles->size(); i++)
    {
        initialize_network(i);
    }
    cout << BLUE << "\nTABLA DE RUTAS" << RESET_COLOR << endl;
    for (int i = 0; i < cant_routers; i++)
    {
        for (int j = 0; j < cant_routers; j++)
        {
            cout << "Router " << i << " a "
                 << "Router " << j << " = " << TABLA_RUTEO[i][j] << endl;
        }
        cout << endl;
    }
}
