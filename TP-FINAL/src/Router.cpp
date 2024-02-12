#include "../include/Router.h"
#include "../include/Lista.h"
#include "../include/Pagina.h"
#include "../include/Paquete.h"
#include "../include/Terminal.h"

#define GREEN "\x1b[32m"
#define RESET_COLOR "\x1b[0m"
#define INFI 9999

using namespace std;

/** Agrega una terminal a la lista del router
 * @param t puntero tipo Terminal
 */
void Router::add_terminal(Terminal *t) {
	terminales_conectados->addFinal(t);
	// t->add_router(this);
}

/** Agrega un router vecino a la lista del router
 * @param r puntero tipo Router
 */
void Router::add_neighbors(Router *r) { routers_vecinos->addFinal(r); }

/* Recibe cada una de las paginas, la divide en paquetes y los encola para su posterior envio
 */
void Router::receive_page() {
	for (int i = 0; i < terminales_conectados->size(); i++) {
		Lista<Pagina *> *pages = terminales_conectados->search_id(i)->getPages();
		if (pages->esvacia()) {
			continue;
		}

		Nodo<Pagina *> *aux = pages->get_czo();

		for (int j = 0; j < pages->size(); j++) {
			Pagina *p = aux->get_dato();
			if (p->getArrived() == false) {
				int n = 1;
				int size_pak = 0;
				int size_pag = p->getSize();

				// Busqueda del minimo comun multiplo
				for (int i = 2; i < size_pag; i++) {
					if (size_pag % i == 0) {
						n = i;
						size_pak = size_pag / i;
					}
				}
				// (en caso de ser numero primo)
				if (n == 1) {
					n = p->getSize();
					size_pak = 1;
				}
				// cout << "Cantidad de paquetes: " << n << " de tamaño: " << size_pak << endl;
				int origen[2] = {0, 0};
				origen[0] = p->getOrigin()[0];
				origen[1] = p->getOrigin()[1];
				int destino[2] = {0, 0};
				destino[0] = p->getDest()[0];
				destino[1] = p->getDest()[1];
				int page_id = p->getId();

				// Se crean n paquetes y se encolan todos en la cola de salida
				for (int j = 0; j < n; j++) {
					Paquete *aux = new Paquete(j, origen, destino, page_id, size_pak, size_pag);
					outPackets->addFinal(aux);
				}

				delete p;
			} else {
				aux = aux->get_next();
			}
		}
	}
	print_outPackets(); // Imprime los paquetes que se van a enviar, solo para debuggear
}
/* Decide el destino del paquete recibido por el router */
void Router::receive_packet() {
	if (!canales_vuelta->esvacia()) {
		for (int i = 0; i < canales_vuelta->size(); i++) {
			int cant_lim = canales_vuelta->search_id(i)->getBw();
			while (cant_lim > 0) // Mientras haya ancho de banda disponible
			{
				Paquete *pkg = canales_vuelta->search_id(i)->transmit_packet();
				if (pkg != NULL) {
					if (pkg->getDestino()[0] == this->getId()) // Si el destino es el router actual
					{
						inPackets->addFinal(pkg);
						canales_vuelta->search_id(i)->getBuffer()->borrarDato(pkg);
						cant_lim--;
					} else { // en caso que deba seguir de viaje el paquete
						outPackets->addFinal(pkg);
						canales_vuelta->search_id(i)->getBuffer()->borrarDato(pkg);
						cant_lim--;
					}
				} else {
					break; // No quedan mas paquetes en el buffer del canal
				}
			}
		}
	}

	if (!inPackets->esvacia()) {
		Paquete *aux = inPackets->cabeza();

		if (check_completion(aux)) {
			int destino_t = aux->getDestino()[1];
			Pagina *page = recreate_page(aux);
			terminales_conectados->search_id(destino_t)->recibir_pagina(page);
		}
	}
}

/** Recrea la pagina luego de juntar todos los paquetes necesarios
 * @param pkg puntero tipo Paquete de muestra
 * @returns puntero tipo Pagina
 */
Pagina *Router::recreate_page(Paquete *pkg) {
	int page_id = pkg->getPageId();
	int origen[2] = {pkg->getOrigen()[0], pkg->getOrigen()[1]};
	int destino[2] = {pkg->getDestino()[0], pkg->getDestino()[1]};
	int page_size = pkg->getSizePag();
	Nodo<Paquete *> *aux = inPackets->get_czo();

	do {
		if (aux->get_dato()->getPageId() == page_id) {
			Nodo<Paquete *> *temp = aux;
			aux = aux->get_next();
			inPackets->borrarDato(temp->get_dato());
		} else {
			aux = aux->get_next();
		}
	} while (aux->get_next() != NULL);

	if (check_erasing(page_id)) {
		cout << "Se han borrado todos los paquetes correctamente\n";
		Pagina *page = new Pagina(page_id, page_size, origen, destino);
		page->setArrived();
		return page;
	} else {
		cout << "Error en la creacion de la pagina\n";
		return NULL;
	}
}

/** Comprueba si los paquetes que tienen de destino al router
 *  son todos los necesarios para crear la pagina correspondiente
 * @param pkg puntero tipo Paquete de muestra para chequear
 * @returns booleano
 */
bool Router::check_completion(Paquete *pkg) {
	int cant = 0;
	Nodo<Paquete *> *aux = inPackets->get_czo();

	for (int i = 0; i < this->inPackets->size(); i++) {
		if (aux->get_dato()->getPageId() == pkg->getPageId()) {
			cant++;
		}
		aux = aux->get_next();
	}

	int size = cant * pkg->getSize();

	if (size == pkg->getSizePag()) {
		return true;
	}
	return false;
}

/* Prints packets to be send */
void Router::print_outPackets() {
	if (outPackets->esvacia()) {
		// cout << "- No hay paquetes para enviar -" << endl;
		return;
	}
	cout << GREEN << "          Paquetes del Router " << this->getId() << RESET_COLOR << "      " << endl;
	cout << "Num_paquete | Origen | Destino | Id_Pagina" << endl;
	Nodo<Paquete *> *aux = outPackets->get_czo();
	for (int i = 0; i < outPackets->size(); i++) {
		cout << aux->get_dato()->getId() << "              " << aux->get_dato()->getOrigen()[0] << ":" << aux->get_dato()->getOrigen()[1] << "       " << aux->get_dato()->getDestino()[0] << ":"
			 << aux->get_dato()->getDestino()[1] << "        " << aux->get_dato()->getPageId() << endl;
		aux = aux->get_next();
	}
	cout << endl;
}

/* Prints received packets */
void Router::print_inPackets() {
	if (inPackets->esvacia()) {
		// cout << "- No hay paquetes recibidos -" << endl;
		return;
	}
	cout << GREEN << "          Paquetes del Router " << this->getId() << RESET_COLOR << "      " << endl;
	cout << "Num_paquete | Origen | Destino | Id_Pagina | Progress (%)" << endl;
	Nodo<Paquete *> *aux = inPackets->get_czo();
	int actual = 0;
	for (int i = 0; i < inPackets->size(); i++) {
		int size_pag = aux->get_dato()->getSizePag();
		int size_pak = aux->get_dato()->getSize();
		int total = size_pag / size_pak;
		(actual != total) ? (++actual) : (actual = total);
		cout << aux->get_dato()->getId() << "              " << aux->get_dato()->getOrigen()[0] << ":" << aux->get_dato()->getOrigen()[1] << "       " << aux->get_dato()->getDestino()[0] << ":"
			 << aux->get_dato()->getDestino()[1] << "        " << aux->get_dato()->getPageId() << "            [" << actual << "/" << total << "]" << endl;
		Nodo<Paquete *> *aux2 = aux;
		if (aux2->get_next() == NULL) // Si es el ultimo paquete de la lista
		{
			cout << endl;
		} else {
			aux = aux->get_next();
		}
	}
	cout << endl;
}

/* Envia el paquete al router vecino correspondiente */
void Router::send_packet() {
	static int first_time = 0; // Bandera para que solo se ejecute una vez
	if (first_time == 0)
		this->receive_page(); // Recibe las paginas y las separa en paquetes
	first_time++;

	int c_totales = canales_ida->size();
	int *bw = new int[c_totales];

	for (int i = 0; i < c_totales; i++) {
		bw[i] = canales_ida->search_id(i)->getBw(); // Guarda el ancho de banda de cada canal
	}

	for (int k = 0; k < outPackets->size(); k++) {
		if (!outPackets->esvacia()) {
			Nodo<Paquete *> *aux = outPackets->get_czo();
			int destino = aux->get_dato()->getDestino()[0];
			int canal_opt = ruta_optima(destino); // Busca el canal optimo de la ruta, el cual tiene el menor peso

			if (destino == this->getId()) // Si el destino es el mismo router
			{
				inPackets->addFinal(aux->get_dato());
				outPackets->borrar();
				continue;
			} else if (canal_opt != -1) // Si hay una ruta disponible al destino (sea vecino o no)
			{
				if (bw[canal_opt] > 0) {
					canales_ida->search_id(canal_opt)->add_packet(aux->get_dato());
					outPackets->borrar();
					bw[canal_opt]--;
				}
			} else {
				cout << "No hay ruta disponible\n";
				break;
			}
		} else {
			break;
		}
	}
	delete[] bw;
}

/** Retorna si un router es vecino o no
 * @param id_r id del router a comprobar
 * @returns booleano
 */
bool Router::es_vecino(int id_r) {
	for (int i = 0; i < routers_vecinos->size(); i++) {
		if (routers_vecinos->search_id(i)->getId() == id_r) {
			return true;
		}
	}
	return false;
}

/** Retorna el id del router vecino en caso de existir
 * @param destino id del router destino
 * @returns id del canal correspondiente al router vecino
 */
int Router::canal_vecino(int destino) {
	if (es_vecino(destino)) {
		for (int j = 0; j < canales_ida->size(); j++) {
			if (canales_ida->search_id(j)->getDestino() == destino) {
				return j; // Retorna el id del canal al router vecino
			}
		}
	}

	return -1; // El destino no es un router vecino
}

/** Agrega una tabla de routers disponibles al Router
 * @param tabla puntero tipo Lista de Rutas
 */
void Router::add_tabla(Lista<Ruta *> *tabla) { this->rutas_disponibles = tabla; }

/* Imprime las rutas disponibles */
void Router::print_rutas() {
	if (this->getRutas()->esvacia()) {
		cout << "No hay rutas disponibles" << endl;
		return;
	}
	cout << GREEN << "Rutas disponibles del Router " << this->getId() << RESET_COLOR << endl;
	cout << "Siguiente | Destino | Distancia_total" << endl;
	Nodo<Ruta *> *aux = rutas_disponibles->get_czo();
	for (int i = 0; i < rutas_disponibles->size(); i++) {
		cout << aux->get_dato()->getNext() << "          " << aux->get_dato()->getLast() << "          " << aux->get_dato()->getDistancia() << endl;
		aux = aux->get_next();
	}
	cout << endl;
}

/** Calculo de la ruta optima del envio de paquetes
 * @param destino id del router destino
 * @returns id del canal correspondiente al router vecino de la ruta optima
 */
int Router::ruta_optima(int destino) {
	int canal_optimo = 0;
	int dist_actual = 0;
	int dist_optima = INFI; // Inicializa la distancia optima en un numero grande

	// Busca la ruta optima al destino
	for (int i = 0; i < this->getRutas()->size(); i++) {
		if (destino == this->getRutas()->search_id(i)->getLast()) {
			dist_actual = this->getRutas()->search_id(i)->getDistancia();
			if (dist_actual <= dist_optima) {
				dist_optima = dist_actual;
				canal_optimo = this->getRutas()->search_id(i)->getNext();
			}
		}
	}

	// Busca el canal correspondiente al router vecino de la ruta optima
	for (int j = 0; j < canales_ida->size(); j++) {
		if (canales_ida->search_id(j)->getDestino() == canal_optimo) {
			return j; // Retorna el id del canal correspondiente al router vecino de la ruta optima
		}
	}
	return -1;
}

/** Chequeo del borrado correcto de los paquetes
 * previo a la creacion de la pagina
 * @param id identificador de la pagina a chequear
 * @return booleano
 */
bool Router ::check_erasing(int id) {
	Nodo<Paquete *> *aux = inPackets->get_czo();

	for (int i = 0; i < inPackets->size(); i++) {
		if (aux->get_dato()->getPageId() == id) {
			return false;
		}
		aux = aux->get_next();
	}
	return true;
}
