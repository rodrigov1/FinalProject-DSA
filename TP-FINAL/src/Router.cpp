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

void Router::divide_page(Pagina *p)
{
    int n;
    for (int i = 1; i < p->getSize(); i++)
    {
        if (p->getSize() % i == 0)
        {
            n = i;
        }
    }
    if (n == 1)
    {
        cout << "El numero de paquetes es: " << p->getSize() << endl;
        return;
    }
    else
    {
        cout << "El numero de paquetes es: " << n << endl;
        return;
    }
}