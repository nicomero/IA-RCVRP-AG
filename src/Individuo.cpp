#include <iostream>     // std::cout
#include <algorithm>    // std::random_shuffle
#include <vector>       // std::vector
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand
#include <math.h>

#include "Nodo.h"
#include "Individuo.h"

Individuo::Individuo( std::vector<Nodo> cities, float maxRiesgo ) :calidad(), tour(), retorno(){

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
            this->retorno.push_back(1);
            demandaAc = 0;
            riesgoAc = 0;
        }
        else{
            this->retorno.push_back(0);
        }

    }

    tour.push_back(cities[i]);
    retorno.push_back(1);

    for (i=0 ; i < this->tour.size() ; i++){
        std::cout << this->tour[i].numero << "--";
    }
    std::cout << '\n';
    for (i=0 ; i < this->retorno.size() ; i++){
        std::cout << this->retorno[i] << "--";
    }

    //evaluar(maxRiesgo);
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

void Individuo::mutar( float maxRiesgo ){

    int n = (int) this->tour.size();

    std::srand ( unsigned ( std::time(0) ) );

    int lugar1 = 1+ (std::rand()% (n-1));
    int lugar2 = 1+ (std::rand()% (n-1));

    iter_swap(this->tour.begin() + lugar1, this->tour.begin() + lugar2);

    for (unsigned i=0 ; i < this->tour.size() ; i++){
        std::cout << this->tour[i].numero << "--";
    }

    n = (int) this->retorno.size();
    lugar1 = (std::rand()% (n-1));

    if(retorno[lugar1] == 0){
        retorno[lugar1] = 1;
    }
    else{
        retorno[lugar1] = 0;
    }

    std::cout << "\n";

    for (unsigned i=0 ; i < this->retorno.size() ; i++){
        std::cout << this->retorno[i] << "--";
    }

    //evaluar( maxRiesgo );

};

void Individuo::evaluar( float maxRiesgo ){

    float deltaRiesgo=0;
    float riesgoAc=0;
    float distAc=0;
    int demandAc=0;
    float autos=0;

    for (unsigned i=0 ; i < this->tour.size()-1 ; i++){
        if (this->tour[i].numero == 0){
            if (riesgoAc > maxRiesgo){
                    deltaRiesgo += riesgoAc - maxRiesgo;
            }
            riesgoAc=0;
            demandAc=0;
            autos+=1;
        }
        distAc += distancia(this->tour[i], this->tour[i+1]);
        demandAc += this->tour[i].demanda;
        riesgoAc += riesgo(riesgoAc, this->tour[i], this->tour[i+1], demandAc);

    }

    this->calidad = distAc + deltaRiesgo + autos;

};
