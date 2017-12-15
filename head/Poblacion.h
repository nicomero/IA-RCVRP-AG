#ifndef POBLACION_H
#define POBLACION_H
#include <vector>

#include "Nodo.h"
#include "Individuo.h"

class Poblacion{
public:
    int n; //cantidad de nodos
    float maxRiesgo;    //maximmo riesgo permitido
    std::vector<Nodo> cities;   //Nodos posibles de las instancias
    std::vector<Individuo> residentes; //poblacion

    Poblacion(std::string s);   //constructor

    void cruzar(Individuo &padre, Individuo &madre);    //cruza 2 individuos
    void cruzaMasiva(); //cruza la poblacion

};
#endif
