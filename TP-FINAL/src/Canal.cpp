#include "../include/Canal.h"
#include "../include/Paquete.h"

using namespace std;

/** Agrega el paquete al buffer del canal
 * @param p puntero tipo Paquete a agregar
 */
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
Paquete *Canal::transmit_packet()
{
    Paquete *aux = NULL;
    aux = buffer->get_czo()->get_dato();
    if (aux != NULL)
    {
        return aux;
    }
    else
    {
        return NULL;
    }
}
