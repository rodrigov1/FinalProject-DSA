#ifndef ADMINISTRADOR_H

#define ADMINISTRADOR_H

#include "Router.h"

class Administrador
{
private:
    Lista<Router *> *routers_disponibles;
    Lista<Terminal *> *terminales_disponibles;
    int cant_terminals;
    int cant_routers;

public:
    Administrador()
    {
        cant_terminals = 0;
        cant_routers = 0;
        routers_disponibles = new Lista<Router *>();
        terminales_disponibles = new Lista<Terminal *>();
    };
    //~Administrador();
    void crearPagina();
    void crear_routers(int cant_routers);
    int get_routers() { return cant_routers; }
    int get_terminals() { return cant_terminals; }
    void conectar_terminales(int t);
    void leer_config();
    int generateRandomNumbers();
};

#endif