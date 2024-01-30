#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include "../include/Lista.h"
#include "../include/Router.h"
#include "../include/Pagina.h"
#include "../include/Terminal.h"
#include "../include/Administrador.h"
#include "../include/Canal.h"

using namespace std;
#define BLUE "\033[36;1m"
#define RESET_COLOR "\x1b[0m"

/* Lector del archivo configuracion.txt */
void Administrador::leer_config()
{
    srand(time(0)); // Seed the random number generator with the current time
    ifstream config_file("config.txt");
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

    crear_routers(num_routers);         // crea los routers
    conectar_terminales(num_terminals); // llama al conector de terminales a routers

    // Skip the next line
    getline(config_file, line);
    getline(config_file, line);

    int origen, destino, bw;
    config_file >> origen;

    while (!config_file.eof())
    {
        config_file >> destino;
        config_file >> bw;
        establecer_conexion(origen, destino, bw);
        config_file >> origen;
    }
    config_file.close();
}

/* Creador de routers */
void Administrador::crear_routers(int r)
{
    cant_routers += r;
    for (int i = 0; i < r; i++)
    {
        Router *router = new Router(i);
        routers_disponibles->addFinal(router);
    }
}

/* Conector de terminales a routers */
void Administrador::conectar_terminales(int t)
{
    cant_terminals += t;
    Nodo<Router *> *aux = routers_disponibles->get_czo();

    for (int i = 0; i < cant_routers; i++)
    {
        // Creo la cantidad "t" de terminales para cada router
        for (int j = 0; j < t; j++)
        {
            Terminal *te = new Terminal(i, j);
            aux->get_dato()->add_terminal(te);
            terminales_disponibles->addFinal(te); // Lista de todos los terminales que ve el administrador
        }
        aux = aux->get_next(); // Paso al siguiente router de la lista
    }
}

/* Imprime los router disponibles */
void Administrador::print_r()
{
    Nodo<Router *> *aux = routers_disponibles->get_czo();
    for (int i = 0; i < routers_disponibles->size(); i++)
    {
        cout << "Router: " << aux->get_dato()->getId() << endl;
        aux = aux->get_next();
    }
}

/* Imprime los terminales disponibles */
void Administrador::print_t()
{
    Nodo<Terminal *> *aux = terminales_disponibles->get_czo();
    for (int i = 0; i < terminales_disponibles->size(); i++)
    {
        cout << "Terminal: " << aux->get_dato()->getIP()[0] << ":" << aux->get_dato()->getIP()[1] << endl;
        aux = aux->get_next();
    }
}

/* Creates a new page and sends it to the appropriate terminal */
void Administrador::crear_pagina()
{
    int origen_r = rand() % cant_routers;
    int origen_t = rand() % cant_terminals;
    int origen[2] = {origen_r, origen_t};
    int destino_r = rand() % cant_routers;
    int destino_t = rand() % cant_terminals;
    int destino[2] = {destino_r, destino_t};
    int size = rand() % 100;
    Pagina *pagina = new Pagina(id_paginas, size, origen, destino);
    // cout << "Pagina creada: " << pagina->getId() << " de tamaño " << pagina->getSize() << endl;
    id_paginas++;

    if (origen != destino)
    {
        // cout << "Pagina " << pagina->getId() << "recibida " << endl;
        this->routers_disponibles->search_id(origen[0])->receive_page(pagina);
    }
    else
    {
        this->routers_disponibles->search_id(origen[0])->getTerminals()->search_id(origen[1])->recibir_pagina(pagina);
    }
}

/* Establece las conexiones de la red de routers */
void Administrador::establecer_conexion(int origen, int destino, int bw)
{
    Canal *c = new Canal(origen, destino, bw);
    routers_disponibles->search_id(origen)->getCanales()->addFinal(c);
    routers_disponibles->search_id(origen)->add_neighbors(routers_disponibles->search_id(destino));
    canales_totales->addFinal(c);
}

/* Ejecuta el envio sistemico de paquetes */
void Administrador::send_packets()
{
    Nodo<Router *> *aux = routers_disponibles->get_czo();
    for (int i = 0; i < routers_disponibles->size(); i++)
    {
        aux->get_dato()->send_packet();
        aux->get_dato()->print_packets();
        aux = aux->get_next();
    }
}

/**
 * Initializes the network by calculating the weights of the routers' connections.
 * The weight represents the cost or distance between routers in the network.
 *
 * @param source The index of the source router.
 */
void Administrador::init_network(int source)
{
    int peso[cant_routers];
    int aux = -1;

    for (int i = 0; i < routers_disponibles->size(); i++) // Inicializa el arreglo de pesos
    {
        if (i == source) // Analisis de peso para el router origen
        {
            peso[source] = 0;
        }
        else if (routers_disponibles->search_id(source)->es_vecino(i)) // Analisis de peso para los vecinos del router origen
        {
            for (int j = 0; j < canales_totales->size(); j++)
            {
                if (canales_totales->search_id(j)->getOrigen() == source && canales_totales->search_id(j)->getDestino() == i)
                {
                    canales_totales->search_id(j)->calcular_peso();
                    aux = canales_totales->search_id(j)->getPeso();
                    // cout << "Peso del canal " << canales_totales->search_id(j)->getOrigen() << " a " << canales_totales->search_id(j)->getDestino() << " es " << canales_totales->search_id(j)->getPeso() << endl;
                }
            }
            peso[i] = aux;
        }
        else
        {

            peso[i] = INFI;
        }
    }

    for (int i = 0; i < cant_routers; i++)
    {
        TABLA_RUTEO[source][i] = peso[i];
    }
}
void Administrador::print_network()
{
    cout << BLUE << "\nTABLA DE RUTAS" << RESET_COLOR << endl;
    for (int i = 0; i < cant_routers; i++)
    {
        for (int j = 0; j < cant_routers; j++)
        {
            cout << "Router " << i << " a "
                 << "Router " << j << " = " << TABLA_RUTEO[i][j] << endl;
        }
        cout << endl;
    }
}

// C[i][j] Costo del arco de i a j
// D[i] costo del camino m�nimo conocido hasta el
//              momento de s a i
//              inicialmente D[s]=0 y D[i]=INFI
// S[i] conjunto de nodos cuya distancia minima a s es conocida
//         y permanente, inicialmente S[] solo contiene a s
//         S[i]=1 si i pertenece, 0 si i no pertenece
// P[i] contiene el vertice que precede a i en el camino
//            minimo encontrado hasta el momento
int *Administrador::dijkstra(int C[][MAX_NODOS], int s, int t, int P[])
{
    static int D[MAX_NODOS];
    int S[MAX_NODOS];
    int actual, i, k, b;
    int menordist, nuevadist;
    // inicializaci�n
    for (i = 0; i < MAX_NODOS; i++)
    {
        S[i] = NO_MIEMBRO;
        D[i] = INFI;
        P[i] = -1;
    } // fin for
    S[s] = MIEMBRO;
    D[s] = 0;
    actual = s;
    b = 1;
    k = 0;
    while ((actual != t) && (b == 1))
    {
        b = 0;
        menordist = INFI;
        // printf("\n\n   D[%i]=%3i ",actual,D[actual]);
        for (i = 0; i < MAX_NODOS; i++)
        {
            // cout<<"\n  i= "<<i;
            if (S[i] == NO_MIEMBRO)
            {
                nuevadist = D[actual] + C[actual][i];
                // printf("\n nuevadist=%3i D[%2i]=%3i ",nuevadist,i,D[i]);
                if (nuevadist < D[i])
                {
                    D[i] = nuevadist; // actual es menor que la anterior
                    P[i] = actual;
                    b = 1;
                } // fin if
                // printf("\n menordist=%3i D[%2i]=%3i ",menordist,i,D[i]);
                if (D[i] < menordist)
                {
                    menordist = D[i];
                    k = i;
                    b = 1; // guardo el nodo de la menor distancia
                }          // fin if
            }              // fin if
        }                  // fin for

        actual = k; // actual se ubica en el nodo de menor distancia
        S[actual] = MIEMBRO;
        // system("PAUSE");
    } // fin while
    return D;
} // fin dijkstra

void Administrador::camino(int P[], int s, int t, int route[])
{
    static int index = 0; // It's static so it doesn't reset every time the function is called recursively
    if (t == s)
    {
        route[index] = s;
        index++;
    }
    else
    {
        camino(P, s, P[t], route);
        route[index] = t;
        index++;
    }
    route[index] = -1; // Marks the end of the array
}

void Administrador::generate_network()
{
    int *pdist, P[MAX_NODOS], s, t;
    for (int i = 0; i < routers_disponibles->size(); i++)
    {
        init_network(i);
    }
    print_network();
    // TEST CASE 1 (s = 0, t = 2)
    s = 0;
    t = 3;
    pdist = dijkstra(TABLA_RUTEO, s, t, P);
    cout << "Distancia minima de " << s << " a " << t << " es " << pdist[t] << endl;
    cout << "Camino: ";
    int route[MAX_NODOS];
    camino(P, s, t, route);
    for (int i = 0; i < cant_routers; i++)
    {
        if (route[i] == -1)
            break;
        cout << route[i] << " ";
    }
    cout << endl;
}