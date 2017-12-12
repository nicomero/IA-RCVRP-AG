#include <iostream>     // std::cout
#include <algorithm>    // std::random_shuffle
#include <vector>       // std::vector
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand
#include <math.h>

#include "Nodo.h"
#include "Individuo.h"

Individuo::Individuo( std::vector<Nodo> cities, float maxRiesgo) :calidad(), tour(), retorno(){

    Nodo origen = cities[0];
    unsigned int i;
    float riesgoAc=0.0;
    int demandaAc=0;

    std::random_shuffle ( cities.begin()+1, cities.end() ); //desordeno los nodos

    tour.push_back(origen); //agregar el almacen a la ruta

    /*agrear los nodos desordenados y repara ruta cuando se pasa el riesgo maximo*/
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

    /*agregar ultimo punto y volver al almacen*/
    tour.push_back(cities[i]);
    retorno.push_back(1);
/*
    for (i=0 ; i < this->tour.size() ; i++){
        std::cout << this->tour[i].numero << "--";
    }
    std::cout << '\n';
    for (i=0 ; i < this->retorno.size() ; i++){
        std::cout << this->retorno[i] << "--";
    }
    std::cout << "\n____________________________________\n";
*/

    /*evaluar calidad de ruta*/
    evaluar(maxRiesgo);
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

    /*calcular puntos para swap*/
    int lugar1 = 1+ (std::rand()% (n-1));
    int lugar2 = 1+ (std::rand()% (n-1));

    iter_swap(this->tour.begin() + lugar1, this->tour.begin() + lugar2);//hacer swap

    /*MUTACION PUNTOS RETORNO*/
    n = (int) this->retorno.size();
    lugar1 = (std::rand()% (n-1));
    float r;

    for (int i = lugar1; i < n-1; i++) {

        r = ((float) std::rand() / (RAND_MAX));

        if( r < 0.21 ){
            if(retorno[i] == 0){
                retorno[i] = 1;
            }
            else{
                retorno[i] = 0;
            }
        }
    }

    /*recalcular calidad*/
    evaluar( maxRiesgo );

};

void Individuo::evaluar( float maxRiesgo ){

    float deltaRiesgo=0;    //cuanto riesgo se pasa la solucion de lo permitido
    float riesgoAc=0;   //riesgo que se va acumulando en la ruta
    float distAc;   //distancia que se va acumulando
    int demandAc=0; //demanda que se va acumulando
    float autos=1;  //ccantidad de autos utilizados
    unsigned int i=1;

    /*distancia desde el almacen al primer nodo*/
    distAc = distancia(this->tour[0], this->tour[1]);

    /*recorrer el tour y los puntos de retorno*/
    for (i=1 ; i < this->tour.size()-1 ; i++){

        demandAc += this->tour[i].demanda;

        if(this->retorno[i-1] == 1){    //si vuelvo al almacen, calcular lo necesario
            distAc = distancia(this->tour[i], this->tour[0]);
            riesgoAc += riesgo(riesgoAc, this->tour[i], this->tour[0], demandAc);
            if (riesgoAc >maxRiesgo){
                deltaRiesgo += riesgoAc-maxRiesgo;
            }
            riesgoAc =0;
            demandAc = 0;
            autos += 1;
        }
        else{
            distAc = distancia(this->tour[i], this->tour[i+1]);
            riesgoAc += riesgo(riesgoAc, this->tour[i], this->tour[i+1], demandAc);
        }
    }

    demandAc += this->tour[i].demanda;
    distAc = distancia(this->tour[i], this->tour[0]);
    riesgoAc += riesgo(riesgoAc, this->tour[i], this->tour[0], demandAc);
    if (riesgoAc >maxRiesgo){
        deltaRiesgo += riesgoAc-maxRiesgo;
    }

    this->calidad = distAc + deltaRiesgo + autos;

};
