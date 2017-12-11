#ifndef POBLACION_H
#define POBLACION_H
#include <vector>

#include "Nodo.h"
#include "Individuo.h"

class Poblacion{
public:
    int n;
    float maxRiesgo;
    std::vector<Nodo> cities;
    std::vector<Individuo> residentes;

    Poblacion(std::string s);
    void mutarMasivo();
    void cruzar(Individuo &padre, Individuo &madre);
};
#endif
