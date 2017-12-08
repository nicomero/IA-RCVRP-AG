#include <iostream>
#include <fstream>
#include <string>

#include "Nodo.h"
#include "Poblacion.h"
#include "Individuo.h"

int main(void)
{

    Nodo antiago = Nodo(0, 0.0, 0.0, 0);
    Nodo bacalao = Nodo(1, 9.0, 0.0, 3);
    std::string s = "Instancias-RCVRP/SET R/4_1_1.0.txt";
    Poblacion mundo = Poblacion(s);

    Individuo nico = Individuo(mundo.cities, mundo.maxRiesgo);

    std::cout << "Hola " << antiago.numero << '\n';
    std::cout << ".... " << nico.calidad << '\n';
    std::cout << "distancia " << nico.distancia(mundo.cities[0],mundo.cities[1]) << '\n';
    std::cout << "riesgo" << nico.riesgo(8.0, antiago, bacalao, 4) << '\n';
    std::cout << "chao " << mundo.maxRiesgo;


    return 0;
}
