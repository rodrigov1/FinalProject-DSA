#include "../include/Administrador.h"
#include "../include/Canal.h"
#include "../include/Lista.h"
#include "../include/Router.h"
#include "../include/Ruta.h"
#include "../include/Terminal.h"
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>

using namespace std;

#define PURPLE "\033[35;1m"
#define BLUE "\033[36;1m"
#define RESET_COLOR "\x1b[0m"

/* Lector del archivo configuracion.txt */
void Administrador::leer_config() {
	srand(time(0)); // Seed the random number generator with the current time
	int opcion = 1;
	string config_name;
	cout << BLUE << "¿Qué archivo config.txt desea usar? 1 para config.txt y 2 para config2.txt" << RESET_COLOR << endl;
	cin >> opcion;
	if (opcion != 2) {
		config_name = "config.txt";
	} else {
		config_name = "config2.txt";
	}
	ifstream config_file(config_name);
	string line;
	int num_routers, num_terminals;
	// Skip the first line
	getline(config_file, line);

	// Read the number of routers
	config_file >> num_routers;

	// Skips the next line
	getline(config_file, line);
	getline(config_file, line);

	config_file >> num_terminals;

	crear_routers(num_routers);			// crea los routers
	conectar_terminales(num_terminals); // llama al conector de terminales a routers

	// Skip the next line
	getline(config_file, line);
	getline(config_file, line);

	int origen, destino, bw;
	config_file >> origen;

	while (!config_file.eof()) {
		config_file >> destino;
		config_file >> bw;
		establecer_conexion(origen, destino, bw);
		config_file >> origen;
	}
	config_file.close();
}

/** Creador de routers
 * @param r cantidad de routers a crear
 */
void Administrador::crear_routers(int r) {
	cant_routers += r;
	if (cant_routers > 256)
		cant_routers = 256;
	for (int i = 0; i < cant_routers; i++) {
		Router *router = new Router(i);
		routers_disponibles->addFinal(router);
	}
}

/** Conector de terminales a routers
 * @param t numero de terminales a crear y conectar
 */
void Administrador::conectar_terminales(int t) {
	cant_terminals += t;
	Nodo<Router *> *aux = routers_disponibles->get_czo();
	if (cant_terminals > 256)
		cant_terminals = 256;
	for (int i = 0; i < cant_routers; i++) {
		// Creo la cantidad "t" de terminales para cada router
		for (int j = 0; j < cant_terminals; j++) {
			Terminal *te = new Terminal(i, j);
			aux->get_dato()->add_terminal(te);
			terminales_disponibles->addFinal(te); // Lista de todos los terminales que ve el administrador
		}
		aux = aux->get_next(); // Paso al siguiente router de la lista
	}
}

/* Imprime los router disponibles */
void Administrador::print_r() {
	Nodo<Router *> *aux = routers_disponibles->get_czo();
	for (int i = 0; i < routers_disponibles->size(); i++) {
		cout << "Router: " << aux->get_dato()->getId() << endl;
		aux = aux->get_next();
	}
}

/* Imprime los terminales disponibles */
void Administrador::print_t() {
	Nodo<Terminal *> *aux = terminales_disponibles->get_czo();
	for (int i = 0; i < terminales_disponibles->size(); i++) {
		cout << "Terminal: " << aux->get_dato()->getIP()[0] << ":" << aux->get_dato()->getIP()[1] << endl;
		aux = aux->get_next();
	}
}

/* Creates a new page and sends it to the appropriate terminal */
void Administrador::administrar_paginas() {
	int cant_pags = rand() % 1;
	if (cant_pags == 0) {
		cant_pags++;
	}
	cout << "Cantidad de paginas creadas: " << cant_pags << "\n" << endl;

	for (int i = 0; i < cant_pags; i++) {
		int origen_r = rand() % cant_routers;
		int origen_t = rand() % cant_terminals;
		int origen[2] = {origen_r, origen_t};
		int destino_r = rand() % cant_routers;
		int destino_t = rand() % cant_terminals;
		int destino[2] = {destino_r, destino_t};
		int size = rand() % 20;
		if (size == 0) {
			size++;
		}
		int num_terminal = origen_t + (origen_r * cant_terminals); // Calculo la posicion del terminal en la lista
																   /* cout << "Pagina creada en: " << origen[0] << ":" << origen[1] << " con destino a: " << destino[0] << ":" << destino[1] << endl; */
		this->terminales_disponibles->search_id(num_terminal)->create_page(this->id_paginas, size, origen, destino);
		id_paginas++;
	}
}

/** Establece las conexiones de la red de routers
 * @param origen id del router de origen
 * @param destino id del router de destino
 * @param bw ancho de banda del canal
 */
void Administrador::establecer_conexion(int origen, int destino, int bw) {
	Canal *c = new Canal(origen, destino, bw);
	routers_disponibles->search_id(origen)->getCanalesIda()->addFinal(c);
	routers_disponibles->search_id(destino)->getCanalesVuelta()->addFinal(c);
	routers_disponibles->search_id(origen)->add_neighbors(routers_disponibles->search_id(destino));
	canales_totales->addFinal(c);
}

/** Imprime los paquetes en transito */
void Administrador::print_packets() {
	Nodo<Router *> *aux = routers_disponibles->get_czo();
	for (int i = 0; i < routers_disponibles->size(); i++) {
		aux->get_dato()->receive_page();
		aux->get_dato()->print_outPackets();
		aux = aux->get_next();
	}
}

/* Ejecuta el envio sistemico de paquetes */
void Administrador::send_packets() {
	Nodo<Router *> *aux = routers_disponibles->get_czo();
	cout << BLUE << "----------- ENVIO DE PAQUETES ------------" << RESET_COLOR << endl;
	for (int i = 0; i < routers_disponibles->size(); i++) {
		aux->get_dato()->send_packet();
		aux->get_dato()->print_outPackets();
		aux = aux->get_next();
	}
}

/* Ejecuta la recepcion de paquetes */
void Administrador::receive_packets() {
	Nodo<Router *> *aux = routers_disponibles->get_czo();
	cout << BLUE << "--------- RECEPCION DE PAQUETES ----------" << RESET_COLOR << endl;
	for (int i = 0; i < routers_disponibles->size(); i++) {
		aux->get_dato()->receive_packet();
		if (aux->get_dato()->getInPackets()->size() > 0) {
			aux->get_dato()->print_inPackets();
		}
		aux = aux->get_next();
	}
}

/**
 * Initializes the network by calculating the weights of the routers' connections.
 * The weight represents the cost or distance between routers in the network.
 * @param source The index of the source router.
 */
void Administrador::init_network(int source) {
	int peso;
	int aux;

	for (int i = 0; i < routers_disponibles->size(); i++) // Inicializa el arreglo de pesos
	{
		if (i == source) {												 // Analisis de peso para el router origen
			peso = 0;													 // hacia si mismo
		} else if (routers_disponibles->search_id(source)->es_vecino(i)) // Analisis de peso para los vecinos del router origen
		{
			for (int j = 0; j < canales_totales->size(); j++) // busco el canal correspondiente
			{
				if (canales_totales->search_id(j)->getOrigen() == source && canales_totales->search_id(j)->getDestino() == i) {
					aux = canales_totales->search_id(j)->getPeso();
					// cout << "Peso del canal " << canales_totales->search_id(j)->getOrigen() << " a " <<
					// canales_totales->search_id(j)->getDestino() << " es " << canales_totales->search_id(j)->getPeso()
					// << endl;
				}
			}
			peso = aux; // en caso de ser vecino
		} else {
			peso = INFI; // en caso de no ser vecino
		}
		TABLA_RUTEO[source][i] = peso;
	}
}

/* Imprime la tabla de rutas */
void Administrador::print_network() {
	cout << BLUE << "\nTABLA DE RUTAS" << RESET_COLOR << endl;
	for (int i = 0; i < cant_routers; i++) {
		for (int j = 0; j < cant_routers; j++) {
			cout << "Router " << i << " a "
				 << "Router " << j << " = " << TABLA_RUTEO[i][j] << endl;
		}
		cout << endl;
	}
}

/** C[i][j] Costo del arco de i a j
 *  D[i] costo del camino minimo conocido hasta el
 *             momento de s a i
 *              inicialmente D[s]=0 y D[i]=INFI
 *  S[i] conjunto de nodos cuya distancia minima a s es conocida
 *         y permanente, inicialmente S[] solo contiene a s
 *         S[i]=1 si i pertenece, 0 si i no pertenece
 *  P[i] contiene el vertice que precede a i en el camino
 *            minimo encontrado hasta el momento
 *  @param C[][] matriz de pesos
 *  @param s origen
 *  @param t destino
 *  @param P[] arreglo de pesos
 * @return D[] arreglo de distancias minimas
 */
int *Administrador::dijkstra(int C[][MAX_NODOS], int s, int t, int P[]) {
	static int D[MAX_NODOS];
	int S[MAX_NODOS];
	int actual, i, k, b;
	int menordist, nuevadist;
	// inicializacion
	for (i = 0; i < MAX_NODOS; i++) {
		S[i] = NO_MIEMBRO;
		D[i] = INFI;
		P[i] = -1;
	} // fin for
	S[s] = MIEMBRO;
	D[s] = 0;
	actual = s;
	b = 1;
	k = 0;
	while ((actual != t) && (b == 1)) {
		b = 0;
		menordist = INFI;
		// printf("\n\n   D[%i]=%3i ",actual,D[actual]);
		for (i = 0; i < MAX_NODOS; i++) {
			// cout<<"\n  i= "<<i;
			if (S[i] == NO_MIEMBRO) {
				nuevadist = D[actual] + C[actual][i];
				// printf("\n nuevadist=%3i D[%2i]=%3i ",nuevadist,i,D[i]);
				if (nuevadist < D[i]) {
					D[i] = nuevadist; // actual es menor que la anterior
					P[i] = actual;
					b = 1;
				} // fin if
				// printf("\n menordist=%3i D[%2i]=%3i ",menordist,i,D[i]);
				if (D[i] < menordist) {
					menordist = D[i];
					k = i;
					b = 1; // guardo el nodo de la menor distancia
				}		   // fin if
			}			   // fin if
		}				   // fin for

		actual = k; // actual se ubica en el nodo de menor distancia
		S[actual] = MIEMBRO;
		// system("PAUSE");
	} // fin while
	return D;
} // fin dijkstra

/** Recursive function that stores the route from the source to the destination
 * @param P[] arreglo de predecesores
 * @param s origen
 * @param t destino
 * @param route[] ruta
 * @param index indice
 */
void Administrador::camino(int P[], int s, int t, int route[], int &index) {
	if (t == s) {
		route[index] = s;
		index++;
	} else {
		camino(P, s, P[t], route, index);
		if (index < MAX_NODOS) // Check if index is within boundries
		{
			route[index] = t;
			index++;
		}
	}
}

/**
 * Generates the network by initializing the routers and calculating the roads between them.
 * Each router is initialized and the shortest road are calculated using Dijkstra's algorithm.
 * The calculated roads are then added to the corresponding router.
 */
void Administrador::generate_network() {
	int *pdist, P[MAX_NODOS], s, t;
	static int first = 1;
	// inicializacion de la red
	for (int i = 0; i < routers_disponibles->size(); i++) {
		init_network(i);
	}

	// print_network();
	for (s = 0; s < MAX_NODOS; s++) {
		int road[MAX_NODOS]; // Use a static array
		int index = 0;		 // Initialize index for the camino function
		Lista<Ruta *> *tabla_rutas = new Lista<Ruta *>();

		for (t = 0; t < MAX_NODOS; t++) {
			Ruta *c = new Ruta();
			pdist = dijkstra(TABLA_RUTEO, s, t, P); // Con esto, se calcula la ruta más corta
			if (pdist[t] != INFI && pdist[t] > 0) {
				// cout << "Distancia minima de " << s << " a " << t << " es " << pdist[t] << endl;
				camino(P, s, t, road, index);
				c->setNext(road[1]);		 // Aca guardo el siguiente router de la ruta
				c->setLast(road[index - 1]); // Aca guardo el destino
				c->setDistancia(pdist[t]);
				tabla_rutas->addFinal(c);
				index = 0; // Reset index for the next iteration of the loop
			}
		}

		this->routers_disponibles->search_id(s)->add_tabla(tabla_rutas);
		if (first == 1)
			this->routers_disponibles->search_id(s)->print_rutas();
		/* delete tabla_rutas; */
	}
	first = 0;
}

void Administrador::print_pagesArrived() {
	Nodo<Router *> *aux = routers_disponibles->get_czo();
	for (int i = 0; i < routers_disponibles->size(); i++) {
		aux->get_dato()->pages_arrived();
		aux = aux->get_next();
	}
}

int Administrador::menu() {
	int opcion;
	int esperar = 1;
	while (esperar == 1) {
		cout << PURPLE << "---------------- MENU -------------" << RESET_COLOR << endl;
		cout << "0. Detener simulacion" << endl;
		cout << "1. Crear nuevas paginas" << endl;
		cout << "2. Simular envio de paquetes" << endl;
		cout << "3. Simular recepcion de paquetes" << endl;
		cout << "4. Ver paginas que ya han sido recibidas" << endl;
		cout << "5. Continuar" << endl << endl;
		cin >> opcion;
		switch (opcion) {
		case 0:
			return 0;
		case 1:
			this->administrar_paginas();
			break;
		case 2:
			this->send_packets();
			break;
		case 3:
			this->receive_packets();
			break; // Add break to exit the switch statement
		case 4:
			this->print_pagesArrived();
			esperar = 1; // Set esperar to 1 to continue the loop
			break;		 // Add break to exit the switch statement
		case 5:
			esperar = 0;
			break; // Add break to exit the switch statement
		default:
			cout << "Opcion invalida. Por favor, elija una opcion valida." << endl;
		}
	}
	return 1;
}
