#ifndef TERMINAL_H
#define TERMINAL_H

// #include "Router.h"
#include "Lista.h"
#include "Pagina.h"

class Terminal {
  private:
	int ip[2];
	Lista<Pagina *> *pages;

  public:
	Terminal(int a, int b) {
		ip[0] = a, ip[1] = b;
		pages = new Lista<Pagina *>();
	};
	~Terminal();
	int *getIP() { return this->ip; };
	void create_page(int id, int size, int *origen, int *destino);
	void recibir_pagina(Pagina *page);
	Lista<Pagina *> *getPages() { return pages; };
};

#endif
