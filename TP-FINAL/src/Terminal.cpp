#include "../include/Terminal.h"
#include <iostream>
#include <string>

using namespace std;

void Terminal :: sendPage(int dest[2]) 
{
    Pagina* p = new Pagina(0, ip, dest);
    // aca iría la parte donde se envia la pagina al Router pero se me fundio el cerebro
}