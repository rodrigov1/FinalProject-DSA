#include <iostream>
#include <string>
#include "../include/Router.h"
#include "../include/Lista.h"
#include "../include/Pagina.h"
#include "../include/Terminal.h"
#include "../include/Paquete.h"

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
    int n = 1;
    for (int i = 2; i < p->getSize(); i++)
    {
        if (p->getSize() % i == 0)
        {
            n = i;
        }
    }

    if (n == 1)
    {
        n = p->getSize();
        // cout << "El numero de paquetes es: " << p->getSize() << endl;
    }

    // Se crean n paquetes y se encolan todos en la cola de salida
    for (int j = 0; j < n; j++)
    {
        Paquete *aux = new Paquete(j, p);
        // cout << "El paquete " << aux->getId() << endl;
        outPackets.encolar(aux);
    }

    delete p; // borrado del objeto pagina
}

void Router::receive_pages(Paquete *pkg)
{
    inPackets.encolar(pkg);
    // check_files(&inPackets);
}

/*void Router::check_files(Cola<Paquete *> *aux)
{
    // aca se revisa si estan todos los paquetes
}*/