#include "../include/Canal.h"
#include "../include/Paquete.h"

using namespace std;

/** Agrega el paquete al buffer del canal
 * @param p puntero tipo Paquete a agregar
 */
void Canal::add_packet(Paquete *p) { buffer->addFinal(p); }

/* Refresca el valor del peso del Canal */
void Canal::calcular_peso() {
	int size = buffer->size();
	if (size == 0 || size < bw) {
		peso = 1;
	} else {
		peso = size / bw;
	}
}

/* Transmite el paquete siguiente en la lista */
Paquete *Canal::transmit_packet() {
	Paquete *aux = buffer->get_czo()->get_dato();
	if (aux != NULL) {
		return aux;
	} else {
		return NULL;
	}
}
