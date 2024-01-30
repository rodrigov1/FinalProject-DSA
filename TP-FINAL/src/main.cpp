#include "../include/Lista.h"
#include "../include/Administrador.h"

int main()
{
    Administrador *admin = new Administrador();
    admin->leer_config();
    admin->crear_pagina();
    admin->print_network();
    // admin->crear_pagina();
    // admin->crear_pagina();
    int opcion = 0;
    while (opcion == 0)
    {
        cout << "Ingrese 1 para enviar paquetes" << endl;
        cout << "Ingrese 2 para recibir paquetes" << endl;
        cout << "Ingrese 3 para salir" << endl;
        cin >> opcion;
        if (opcion == 1)
        {
            admin->send_packets();
            opcion = 0;
        }
        else if (opcion == 2)
        {
            // admin->receive_packets();
            opcion = 0;
        }
        else if (opcion == 3)
        {
            opcion = 1;
        }
        else
        {
            cout << "Ingrese una opcion valida" << endl;
            opcion = 0;
        }
    }
    return 0;
}