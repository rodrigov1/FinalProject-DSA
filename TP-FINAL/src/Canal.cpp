#include "../include/Canal.h"
#include "../include/Paquete.h"

using namespace std;

void Canal::add_packet(Paquete *p)
{
    buffer->addFinal(p);
}

void Canal::calcular_peso()
{
    int size = buffer->size();
    if (size == 0)
    {
        peso = 1;
    }
    else
    {
        peso = size / bw;
    }
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