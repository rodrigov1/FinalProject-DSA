#include "../include/Lista.h"
#include "../include/Administrador.h"

int main()
{

    Administrador *admin = new Administrador();
    admin->leer_config();
    return 0;
}