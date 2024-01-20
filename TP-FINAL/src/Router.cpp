#include <iostream>
#include <string>
#include "../include/Router.h"
#include "../include/Lista.h"
#include "../include/Pagina.h"
#include "../include/Terminal.h"

using namespace std;

void Router::add_terminal(Terminal *t)
{
    terminales_conectados->addFinal(t);
}

void Router::add_neighbors(Router *r)
{
    routers_vecinos->add(r);
}

void Router::recibir_pagina(Pagina *p)
{
    if (p->getDest()[0] == this->getId())
    {
        cout << "Pagina reciba" << endl;
    }
    else
    {
    }
}