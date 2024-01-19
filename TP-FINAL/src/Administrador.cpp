#include <iostream>
// #include "../include/Pagina.h"
#include <fstream>
#include <ctime>
#include <cstdlib>
#include "../include/Lista.h"
#include "../include/Router.h"
#include "../include/Pagina.h"
#include "../include/Terminal.h"
#include "../include/Administrador.h"

using namespace std;

/*Deber´a utilizar n´umeros aleatorios para simular la generaci´on de p´aginas a
ser enviadas, el destino y el tama˜no de cada p´agina.*/

// Function to generate random numbers
int generateRandomNumbers()
{
    srand(time(0)); // Seed the random number generator
    int randomNumbers;
    // Generate random numbers between 0 and 255 without including 255 (byte)
    randomNumbers = rand() % 255;
    return randomNumbers;
}

void Administrador::leer_config()
{
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

    cout << "Numero de routers: " << num_routers << endl;
    cout << "Numero de terminales: " << num_terminals << endl;

    crear_routers(num_routers); // crea los routers

    /*conectar_terminales(cant_terminals); // llama al conector de terminales a routers
    int origen, destino, ancho;
    config_file >> origen;
    while (!config_file.eof()) // mientras no sea el final del archivo
    {
        config_file >> destino;
        config_file >> ancho;
        // establecer_conexion(origen, destino, ancho);
        config_file >> origen; // lee el siguiente origen
    }
    config_file.close();*/
}

void Administrador::crear_routers(int c)
{
    this->cant_routers = c;
    for (int i = 0; i < c; i++)
    {
        Router *router = new Router(i);
        routers_disponibles->addFinal(router);
        cout << "Router creado con id: " << router->getId() << endl;
    }
    cout << "Cantidad de routers creados: " << routers_disponibles->size() << endl;
    this->print_r();
}

/*                                   Conector de terminales a routers           */
void Administrador::conectar_terminales(int t)
{
    this->cant_terminals = t;
    int routers = this->cant_routers;
    Nodo<Router *> *aux = routers_disponibles->get_czo();

    for (int i = 0; i < routers; i++)
    {
        // Creo la cantidad "t" de terminales para cada router
        for (int j = 0; j < t; j++)
        {
            int v[2] = {i, j};
            Terminal *terminal = new Terminal(v);
            aux->get_dato()->add_terminal(terminal);
        }
        aux = aux->get_next(); // Paso al siguiente router de la lista
    }
}

void Administrador::print_r()
{
    Nodo<Router *> *aux = this->routers_disponibles->get_czo();
    for (int i = 0; i < this->routers_disponibles->size(); i++)
    {
        cout << "Router: " << aux->get_dato()->getId() << endl;
        aux = aux->get_next();
    }
}