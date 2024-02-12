#ifndef ROUTER_H
#define ROUTER_H

#include "Canal.h"
#include "Lista.h"
#include "Paquete.h"
#include "Ruta.h"
#include "Terminal.h"

class Router {
  private:
	int id;
	Lista<Router *> *routers_vecinos;
	Lista<Terminal *> *terminales_conectados;

	// Lista<Pagina *> *paginas_enviadas;
	// Lista<Pagina *> *paginas_recibidas;

	Lista<Paquete *> *inPackets;
	Lista<Paquete *> *outPackets;
	Lista<Canal *> *canales_ida;
	Lista<Canal *> *canales_vuelta;
	Lista<Ruta *> *rutas_disponibles = new Lista<Ruta *>();

  public:
	Router(int id) {
		this->id = id;
		routers_vecinos = new Lista<Router *>();
		canales_ida = new Lista<Canal *>();
		canales_vuelta = new Lista<Canal *>();
		terminales_conectados = new Lista<Terminal *>();
		inPackets = new Lista<Paquete *>();
		outPackets = new Cola<Paquete *>();
	};
	~Router();
	void add_terminal(Terminal *t);
	void add_neighbors(Router *r);
	int getId() { return id; };
	Lista<Terminal *> *getTerminals() { return terminales_conectados; };
	Lista<Router *> *getNeighbors() { return routers_vecinos; };
	void receive_page();
	void send_packet();
	Lista<Paquete *> *getInPackets() { return inPackets; };
	Lista<Canal *> *getCanalesIda() { return canales_ida; };
	Lista<Canal *> *getCanalesVuelta() { return canales_vuelta; };
	void receive_packet();
	bool check_completion(Paquete *p);
	bool check_erasing(int id);
	void print_outPackets();
	void print_inPackets();
	Pagina *recreate_page(Paquete *p);
	bool es_vecino(int id_r);
	Lista<Ruta *> *getRutas() { return rutas_disponibles; };
	void add_tabla(Lista<Ruta *> *tabla);
	void print_rutas();
	int ruta_optima(int destino);
	int canal_vecino(int destino);
};

#endif
