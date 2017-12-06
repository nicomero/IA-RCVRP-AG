#ifndef POBLACION_H
#define POBLACION_H
#include <vector>

#include "Nodo.h"

class Poblacion{
public:
    int n;
    float maxRiesgo;
    std::vector<Nodo> cities;

    Poblacion(std::string s);
};
#endif
