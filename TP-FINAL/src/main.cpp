#include "../include/Lista.h"
#include "../include/Administrador.h"

int main()
{
    Administrador *admin = new Administrador();
    admin->leer_config();
    admin->crear_pagina();
    admin->crear_pagina();
    return 0;
}