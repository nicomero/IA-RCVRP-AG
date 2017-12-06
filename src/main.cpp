#include <iostream>
#include <fstream>
#include <string>

#include "Nodo.h"
#include "Poblacion.h"

int main(void)
{

    Nodo santiago = Nodo(0, 1.0, 1.0, 4);
    std::string s = "Instancias-RCVRP/SET O/10.txt";
    Poblacion mundo = Poblacion(s);


    std::cout << "Hola " << santiago.numero << '\n';
    std::cout << "chao " << mundo.maxRiesgo;


    return 0;
}
