#include <iostream>     // std::cout
#include <algorithm>    // std::random_shuffle
#include <vector>       // std::vector
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand
#include <math.h>

#include "Nodo.h"
#include "Individuo.h"

Individuo::Individuo( std::vector<Nodo> cities, float maxRiesgo ) :calidad(), tour(){

    Nodo origen = cities[0];
    unsigned int i;
    float riesgoAc=0.0;
    int demandaAc=0;

    std::srand ( unsigned ( std::time(0) ) );
    std::random_shuffle ( cities.begin()+1, cities.end() );

    tour.push_back(origen);

    for (i=1 ; i < cities.size()-1 ; i++){

        this->tour.push_back(cities[i]);
        demandaAc += cities[i].demanda;
        riesgoAc += riesgo(riesgoAc, cities[i], cities[i+1], demandaAc);

        if (riesgoAc > maxRiesgo){
            this->tour.push_back(origen);
            demandaAc = 0;
            riesgoAc = 0;
        }

    }

    tour.push_back(cities[i]);
    tour.push_back(origen);

    for (i=0 ; i < this->tour.size() ; i++){
        std::cout << this->tour[i].numero << "--";
    }

    this->calidad =  5.0;
};

float Individuo::distancia(Nodo u, Nodo w){

    double dx = pow(u.x-w.x, 2.0);
    double dy =pow(u.y-w.y, 2.0);
    double dtotal = sqrt(dx + dy);
    return (float) dtotal;
};

float Individuo::riesgo(float riesgoPrev, Nodo u, Nodo w, int demandAcum){

    return riesgoPrev + distancia(u, w)*(float)demandAcum;
};

void Individuo::mutar(){

    int n = (int) this->tour.size();

    std::srand ( unsigned ( std::time(0) ) );

    int lugar1 = std::rand()%n;
    int lugar2 = std::rand()%n;

    iter_swap(this->tour.begin() + lugar1, this->tour.begin() + lugar2);

    for (unsigned i=0 ; i < this->tour.size() ; i++){
        std::cout << this->tour[i].numero << "--";
    }



};
/*
void Individuo::evaluar(){

    float deltaRiesgo=0;
    float riesgoAc=0;
    float distAc=0;
    int demandAc=0;

    for (unsigned i=0 ; i < this->tour.size()-1 ; i++){
        distAc += distancia(this->tour[i], this->tour[i+1]);
        demandAc += this->tour[i].;
        riesgoAc += riesgo(riesgoAC, this->tour[i], this->tour[i+1], );

    }

};
*/
