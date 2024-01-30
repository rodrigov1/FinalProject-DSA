#ifndef ADMINISTRADOR_H

#define ADMINISTRADOR_H

#include "Router.h"
#include "Terminal.h"
#include "Lista.h"
#include "Pagina.h"
#include "Canal.h"

class Administrador
{
private:
    Lista<Router *> *routers_disponibles = new Lista<Router *>();
    Lista<Terminal *> *terminales_disponibles = new Lista<Terminal *>();
    Lista<Canal *> *canales_totales = new Lista<Canal *>();
    int cant_terminals = 0;
    int cant_routers = 0;
    int id_paginas = 0;

public:
    Administrador(){};
    ~Administrador();
    void crear_pagina();
    void crear_routers(int r);
    int get_routers() { return cant_routers; }
    int get_terminals() { return cant_terminals; }
    void establecer_conexion(int origen, int destino, int bw);
    void conectar_terminales(int t);
    void leer_config();
    int generateRandomNumbers();
    void print_r();
    void print_t(); // imprime las terminales
    void send_packets();
    // void receive_packets();
    void initialize_network(int source);
    void print_network();
};

#endif