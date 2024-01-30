#include "../include/Lista.h"
#include "../include/Pagina.h"
#include "../include/Terminal.h"

/** Recibe una pagina y la encola para su envio a la red de routers 
 * @param page puntero tipo Pagina a enviar
*/
void Terminal::recibir_pagina(Pagina *page)
{
    pages->encolar(page);
    cout << this->getIP()[0] << "." << this->getIP()[1] << " recibio la pagina " << page->getId() << endl;
}
