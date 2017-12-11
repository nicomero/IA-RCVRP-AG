#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand
#include <set>

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

    std::time_t tiempo = std::time(0);
    std::srand ( unsigned ( tiempo ) );
    for (i=0; i<6 ; i++){

        Individuo raton = Individuo(this->cities , this->maxRiesgo);
        this->residentes.push_back(raton);
    }

    for (auto j : residentes){
        for (auto k : j.tour){
            std::cout << k.numero << "--";
        }
        std::cout << "\n";
        for (auto l : j.retorno){
            std::cout << l << "--";
        }


        std::cout << "\n____________________\n";
    }

    file.close();
};

void Poblacion::mutarMasivo(){

    for (unsigned i=0; i < this->residentes.size(); i++){
        this->residentes[i].mutar(this->maxRiesgo);
    }

    std::cout << "\n*************************************\n";

    for (auto j : this->residentes){
        for (auto k : j.tour){
            std::cout << k.numero << "..";
        }
        std::cout << "\n";
        for (auto l : j.retorno){
            std::cout << l << "..";
        }


        std::cout << "\n____________________\n";
    }


};

void Poblacion::cruzar(Individuo &padre, Individuo &madre){

    unsigned int i;

    std::set<int> enPadre;
    std::set<int> enMadre;

    int lugar1 = 0;
    int lugar2 = 0;

    int lenP = (int) padre.tour.size();
    int lenM = (int) madre.tour.size();

    while(lugar1 == lugar2){

        lugar1 = 1+ (std::rand()% (lenP-1));
        lugar2 = 1+ (std::rand()% (lenM-1));
    }

    if (lugar1 > lugar2){

        int temp = lugar1;
        lugar1 = lugar2;
        lugar2 = temp;
    }

    std::cout << "\nENTRE: " << lugar1 << " Y " << lugar2 <<"\n";

    for (i = 0; i<lugar1 ; i++){

        enPadre.insert(padre.tour[i].numero);
        enMadre.insert(madre.tour[i].numero);

    }

    for (i = lugar2; i<lenP ; i++){

        enPadre.insert(padre.tour[i].numero);
        enMadre.insert(madre.tour[i].numero);

    }

    std::vector<Nodo> cortePadre;
    std::vector<Nodo> corteMadre;

    for (i = lugar1; i<lugar2 ; i++){
        cortePadre.push_back(padre.tour[i]);
        corteMadre.push_back(madre.tour[i]);
    }

    int j = 0;
    int k = 0;

    i=lugar1;
    while (j < corteMadre.size()) {
        if (enPadre.find(corteMadre[j].numero) == enPadre.end()){
            padre.tour[i] = corteMadre[j];
            enPadre.insert(padre.tour[i].numero);
            i++;
        }
        j++;
    }
    while(k < cortePadre.size()){
        if (enPadre.find(cortePadre[k].numero) == enPadre.end()){
            padre.tour[i] = cortePadre[k];
            enPadre.insert(padre.tour[i].numero);
            i++;
        }
        k++;
    }


/////////////////////////////////////////
    j = 0;
    k = 0;

    i=lugar1;
    while (j < cortePadre.size()) {
        if (enMadre.find(cortePadre[j].numero) == enPadre.end()){
            madre.tour[i] = cortePadre[j];
            enMadre.insert(madre.tour[i].numero);
            i++;
        }
        j++;
    }
    while(k < corteMadre.size()){
        if (enMadre.find(corteMadre[k].numero) == enMadre.end()){
            madre.tour[i] = corteMadre[k];
            enMadre.insert(madre.tour[i].numero);
            i++;
        }
        k++;
    }

};
