#include "../include/Terminal.h"
#include "../include/Lista.h"
#include "../include/Pagina.h"

#define RED "\033[31;1m"
#define RESET_COLOR "\x1b[0m"

/** Recibe una pagina y la encola para su envio a la red de routers
 * @param page puntero tipo Pagina a enviar
 */
void Terminal::recibir_pagina(Pagina *page) {
	pages->addFinal(page);
	cout << RED << "\n         " << this->getIP()[0] << "." << this->getIP()[1] << " recibio la pagina " << page->getId() << RESET_COLOR << endl << endl;
}

void Terminal::create_page(int id, int size, int *origen, int *destino) {
	Pagina *page = new Pagina(id, size, origen, destino);
	if (origen[0] == destino[0] && origen[1] == destino[1])
		page->setArrived();
	/* cout << "Pagina creada con id: " << page->getId() << endl; */
	pages->addFinal(page);
}
