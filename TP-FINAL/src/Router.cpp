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
    routers_vecinos->addFinal(r);
}

void Router::receive_page(Pagina *p)
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

void Router::receive_packet(Paquete *pkg)
{
    // cout << "El paquete " << pkg->getId() << " llego al router " << this->getId() << endl;
    if (pkg->getDestino()[0] == this->getId())
    {
        inPackets.encolar(pkg);
        // call check_completion() to see if there are all the packets of a specific page
    }
    else
    {
        // cout << "El paquete " << pkg->getId() << " se envia al router " << pkg->getDestino()[0] << endl;
    }
}
/*void Router::check_files(Cola<Paquete *> *aux)
{
    // aca se revisa si estan todos los paquetes
}*/