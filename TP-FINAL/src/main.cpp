#include "../include/Administrador.h"

#define BLUE "\033[36;1m"
#define PURPLE "\033[35;1m"
#define RESET_COLOR "\x1b[0m"

int main() {
	Administrador *admin = new Administrador();
	admin->leer_config();
	int opcion = 1;
	int crear = 1;
	int ciclos = 0;
	int print_inicial = 1;
	while (opcion == 1) {
<<<<<<< HEAD
		if (ciclos % 2 == 0) {
			cout << "El administrador toma el control" << endl;
=======
		if (ciclos % 2 == 0)
		cout << "El administrador toma el control" << endl;
>>>>>>> 2030bd7ee871ae97e74e8ac9b66a9c212ee08026
			admin->generate_network();
		}
		if (crear == 1) {
			admin->administrar_paginas();
			crear = 0;
		}
		if (print_inicial) {
			admin->print_packets();
			print_inicial = 0;
		}
		cout << BLUE << "----------- ENVIO DE PAQUETES ------------" << RESET_COLOR << endl;
		admin->send_packets();
		cout << BLUE << "--------- RECEPCION DE PAQUETES ----------" << RESET_COLOR << endl;
		admin->receive_packets();
		opcion = admin->menu();
		ciclos++;
	}
	return 0;
}
