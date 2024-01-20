#include "../include/Lista.h"
#include "../include/Pagina.h"
#include "../include/Terminal.h"

void Terminal::recibir_pagina(Pagina *page)
{
    pages->encolar(page);
    cout << this->getIP()[0] << "." << this->getIP()[1] << " recibio la pagina " << page->getId() << endl;
}
