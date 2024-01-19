#include <iostream>
// #include "../include/Pagina.h"
#include <fstream>
#include <ctime>
#include <cstdlib>
#include "../include/Lista.h"
#include "../include/Router.h"
#include "../include/Pagina.h"

using namespace std;

class Administrador
{
private:
    Lista<Router *> routers_disponibles;
    // Lista<Terminal*> terminals;
    int cant_terminals;
    int cant_routers;

public:
    Administrador(){};
    //~Administrador();
    void crearPagina();
    void crearRouters(int cant_routers);
    int get_routers() { return cant_routers; }
    int get_terminals() { return cant_terminals; }
    void leer_config();
    int generateRandomNumbers();
};

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
    ifstream config_file("../config.txt");
    string line;
    int num_routers, num_terminals, num_bandwidth;

    // Skip the first line
    getline(config_file, line);

    // Read the number of routers
    config_file >> num_routers;

    // Skips the next line
    getline(config_file, line);
    getline(config_file, line);

    // Read the number of terminals
    config_file >> num_terminals;

    // Skipsthe next line
    getline(config_file, line);
    getline(config_file, line);

    // Read the bandwidth
    config_file >> num_bandwidth;

    cant_routers = num_routers;
    cant_terminals = num_terminals;

    // Skips the next line
    getline(config_file, line);

    // crearRouters(cant_routers);           // llama al generador de routers
    // conectarTerminales(terminalesPorRouter); // conecta txr por cada router
    int origen, destino, ancho;
    config_file >> origen;
    while (!config_file.eof()) // mientras no sea el final del archivo
    {
        config_file >> destino;
        config_file >> ancho;
        // establecerLazo(origen, destino, ancho);
        config_file >> origen; // lee el siguiente origen
    }
    config_file.close();
}

void Administrador::crearRouters(int cant_routers)
{
    for (int i = 0; i < cant_routers; i++)
    {
        Router *router = new Router(i);
        routers_disponibles.add(router);
    }
}

int main()
{

    return 0;
}