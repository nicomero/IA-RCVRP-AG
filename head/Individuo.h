#ifndef INDIVIDUO_H
#define INDIVIDUO_H
#include <vector>
#include <ctime>
#include "Nodo.h"

class Individuo{
public:
    float calidad; //calida del individuo (mas calidad -> peor solucion)
    std::vector<Nodo> tour; //orden en que recorre los nodos
    std::vector<int> retorno;   //puntos en los que vuelve al almacen
    std::vector<float> miniDistancias;//distancia recorrida por cada subtour
    std::vector<float> miniRiesgos;//riesgo de cada subtour
    bool factible;//indica si es factible

    Individuo(std::vector<Nodo> cities, float maxRiesgo);//constructor
    float distancia(Nodo u, Nodo w);    //calcula la distancia entre 2 nodos
    float riesgo(float riesgoPrev, Nodo u, Nodo w, int demandAcum);//calcula riesgo
    void mutar( float maxRiesgo );  //muta la ruta
    void evaluar( float maxRiesgo );    //evalua la ruta
};
#endif
