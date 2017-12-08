#include <iostream>
#include <fstream>
#include <string>

#include "Nodo.h"
#include "Poblacion.h"
#include "Individuo.h"

int main(void)
{

    Nodo antiago = Nodo(0, 0.0, 0.0, 0);
    std::string s = "Instancias-RCVRP/SET R/4_1_1.0.txt";
    Poblacion mundo = Poblacion(s);

    Individuo nico = Individuo(mundo.cities, mundo.maxRiesgo);

    std::cout << "calidad nico " << nico.calidad << '\n';
    std::cout << "\n_______________ \n";
    nico.mutar(mundo.maxRiesgo);
    std::cout << "\n____________ \n";
    std::cout << "numero nodo " << antiago.numero << '\n';
    std::cout << "calidad nico " << nico.calidad << '\n';
    std::cout << "maximo riesgo " << mundo.maxRiesgo;


    return 0;
}
