#include <iostream>     // std::cout
#include "Nodo.h"

Nodo::Nodo(int i, float ejeX, float ejeY, int d) :numero(i) ,x(ejeX), y(ejeY), demanda(d){
    std::cout << "Se creo un nodo";
};
