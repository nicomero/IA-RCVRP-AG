#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Poblacion.h"
#include "Individuo.h"


Poblacion::Poblacion(std::string s) :n(), maxRiesgo(), cities(), residentes(){

    std::ifstream file{s};  //archivo a leer
    float x, y; //ejes
    int i, d;   //iterador y demanda
    std::vector<int> demanda;
    std::vector<float> ejeX;
    std::vector<float> ejeY;

    if (!file.good()){
        exit (EXIT_FAILURE);
    }

    /*Guardo el numero de nodos y el maximo riesgo permitido*/
    file >> this->n;
    file >> this->maxRiesgo;
    std::cout << this->n << ' ' << this->maxRiesgo << '\n';

    /*Guardo vector de demandas*/
    for (i=0; i<n; i++){
        file >> d;
        demanda.push_back(d);
        std::cout << demanda.at(i) << '\n';
    }

    /*Guardo ejes de cada nodo*/

    for (i=0; i<n; i++){
        file >> x >> y;
        ejeX.push_back(x);
        ejeY.push_back(y);
        std::cout << ejeX.at(i) << ' ' << ejeY.at(i) << '\n';
    }

    for (i=0; i<n; i++){
        Nodo ciudad = Nodo(i, ejeX[i], ejeY[i], demanda[i]);

        this->cities.push_back(ciudad);
        std::cout << this->cities.at(i).numero << ' ' << this->cities.at(i).demanda << '\n';
    }

    for (i=0; i<6 ; i++){

        Individuo raton = Individuo(this->cities , this->maxRiesgo);
        this->residentes.push_back(raton);
    }

    file.close();
};
