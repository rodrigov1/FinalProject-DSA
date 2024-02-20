#include "../include/Administrador.h"

#define BLUE "\033[36;1m"
#define PURPLE "\033[35;1m"
#define RESET_COLOR "\x1b[0m"

int main() {
	Administrador *admin = new Administrador();
	admin->leer_config();
	int opcion = 1;
	int crear = 1;
	int opcion_pag = 0;
	int ciclos = 0;
	while (opcion == 1) {
		if (ciclos % 2 == 0)
			admin->generate_network();
		if (crear == 1) {
			admin->administrar_paginas();
			crear = 0;
		}
		admin->print_packets();
		cout << BLUE << "----------- ENVIO DE PAQUETES ------------" << RESET_COLOR << endl;
		admin->send_packets();
		cout << BLUE << "--------- RECEPCION DE PAQUETES ----------" << RESET_COLOR << endl;
		admin->receive_packets();
		cout << PURPLE << "------- ¿DESEA CREAR NUEVAS PAGINAS? -------" << RESET_COLOR << endl;
		cout << "1. SI" << endl;
		cout << "2. NO" << endl << endl;
		cin >> opcion_pag;
		crear = opcion_pag;
		cout << PURPLE << "------- ¿DESEA REPETIR EL PROCESO? -------" << RESET_COLOR << endl;
		cout << "1. SI" << endl;
		cout << "0. NO" << endl << endl;
		cin >> opcion;
		ciclos++;
	}
	return 0;
}
