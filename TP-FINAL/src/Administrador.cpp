#include <iostream>
#include "../include/Pagina.h"
#include <ctime>
#include <cstdlib>

using namespace std;

/*Deber´a utilizar n´umeros aleatorios para simular la generaci´on de p´aginas a
ser enviadas, el destino y el tama˜no de cada p´agina.*/

// Function to generate random numbers
int generateRandomNumbers()
{
    srand(time(0)); // Seed the random number generator
    int randomNumbers;
    randomNumbers = rand() % +1; // Generates random numbers between 1 and 1000
    return randomNumbers;
}

int main()
{
    // int cant_pages = generateRandomNumbers();
    // cout << cant_pages << endl;
    return 0;
}