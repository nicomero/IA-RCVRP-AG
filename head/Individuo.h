#ifndef INDIVIDUO_H
#define INDIVIDUO_H
#include <vector>
#include "Nodo.h"

class Individuo{
public:
    float calidad;
    std::vector<Nodo> tour;
    std::vector<int> retorno;

    Individuo(std::vector<Nodo> cities, float maxRiesgo );
    float distancia(Nodo u, Nodo w);
    float riesgo(float riesgoPrev, Nodo u, Nodo w, int demandAcum);
    void mutar( float maxRiesgo );
    void evaluar( float maxRiesgo );
};
#endif
