#include "../include/Canal.h"
#include "../include/Paquete.h"

using namespace std;

void Canal::add_packet(Paquete *p)
{
    buffer->addFinal(p);
}

// Paquete *Canal::transmit_packet()
// {
//     int random = rand() % buffer->size();
//     Paquete *aux = NULL;
//     aux = buffer->search_id(random);
//     buffer->borrar(); // Borra el paquete del buffer
//     // cout << "El paquete " << aux->getId() << " se transmitio" << endl;
//     if (aux != NULL)
//     {
//         return aux;
//     }
//     else
//     {
//         return NULL;
//     }
// // }