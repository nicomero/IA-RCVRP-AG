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
    }

    /*Guardo ejes de cada nodo*/

    for (i=0; i<n; i++){
        file >> x >> y;
        ejeX.push_back(x);
        ejeY.push_back(y);
    }

    /*Agrego los nodos en un registro*/
    for (i=0; i<n; i++){
        Nodo ciudad = Nodo(i, ejeX[i], ejeY[i], demanda[i]);

        this->cities.push_back(ciudad);
    }

    /*Genero poblacion de individuos*/
    std::time_t tiempo = std::time(0);
    std::srand ( unsigned ( tiempo ) );
    for (i=0; i<1000 ; i++){

        Individuo raton = Individuo(this->cities , this->maxRiesgo);
        this->residentes.push_back(raton);
    }

    file.close();
};

void Poblacion::cruzar(Individuo &padre, Individuo &madre){

    int i;

    std::set<int> enPadre;  //Indica que nodos ya estan en el padre (para la cruza)
    std::set<int> enMadre;  //Indica que nodos ya estan en la madre (para la cruza)

    int lugar1 = 0; //punto de cruza inicial
    int lugar2 = 0; //punto de cruza final

    int lenP = (int) padre.tour.size(); //largo del padre
    int lenM = (int) madre.tour.size(); //largo de la madre

    /*encontrar 2 puntos de corte diferentes y ordenarlos*/
    while(lugar1 == lugar2){

        lugar1 = 1+ (std::rand()% (lenP-1));
        lugar2 = 1+ (std::rand()% (lenM-1));
    }

    if (lugar1 > lugar2){

        int temp = lugar1;
        lugar1 = lugar2;
        lugar2 = temp;
    }

    /*marcar como existentes los nodos fuera del area de corte*/
    for (i = 0; i<lugar1 ; i++){

        enPadre.insert(padre.tour[i].numero);
        enMadre.insert(madre.tour[i].numero);
    }

    for (i = lugar2; i<lenP ; i++){

        enPadre.insert(padre.tour[i].numero);
        enMadre.insert(madre.tour[i].numero);

    }

    /*TOmar los nodos de cada area de corte*/
    std::vector<Nodo> cortePadre;
    std::vector<Nodo> corteMadre;

    for (i = lugar1; i<lugar2 ; i++){

        cortePadre.push_back(padre.tour[i]);
        corteMadre.push_back(madre.tour[i]);
    }

    unsigned int j = 0;//recorre el area de corte que se quiere poner
    unsigned int k = 0;//recorre el area de corte original

    i=lugar1;//recorre el area donde se quiere poner el are de corte

    /*Alterar al padre*/
    while (j < corteMadre.size()) {//mientras pueda agregar de la otra area

        /*Si el nodo no se encuentra en el individuo*/
        if (enPadre.find(corteMadre[j].numero) == enPadre.end()){

            padre.tour[i] = corteMadre[j];
            enPadre.insert(padre.tour[i].numero);
            i++;
        }
        j++;
    }
    while(k < cortePadre.size()){//mientras pueda agregar de la area propia

        /*Si el nodo no se encuentra en el individuo*/
        if (enPadre.find(cortePadre[k].numero) == enPadre.end()){

            padre.tour[i] = cortePadre[k];
            enPadre.insert(padre.tour[i].numero);
            i++;
        }
        k++;
    }

    j = 0;
    k = 0;

    i=lugar1;

    /*Alterar a la madre*/
    while (j < cortePadre.size()) {//mientras pueda agregar de la otra area

        /*Si el nodo no se encuentra en el individuo*/
        if (enMadre.find(cortePadre[j].numero) == enPadre.end()){

            madre.tour[i] = cortePadre[j];
            enMadre.insert(madre.tour[i].numero);
            i++;
        }
        j++;
    }
    while(k < corteMadre.size()){//mientras pueda agregar de la area propia

        /*Si el nodo no se encuentra en el individuo*/
        if (enMadre.find(corteMadre[k].numero) == enMadre.end()){

            madre.tour[i] = corteMadre[k];
            enMadre.insert(madre.tour[i].numero);
            i++;
        }
        k++;
    }

    /*Mutacion del retorno*/

    int temp;
    for (int z = lugar1-1; z < lugar2-1 ; z++) {

        temp = padre.retorno[z];
        padre.retorno[z] = madre.retorno[z];
        madre.retorno[z] = temp;
    }

    //padre.evaluar(this->maxRiesgo);
    //madre.evaluar(this->maxRiesgo);

};

void Poblacion::cruzaMasiva(){

    std::vector<Individuo> nextGen; //vector donde se guarda la siguiente generacion
    Individuo best = this->residentes[0];   //elitismo mejor
    Individuo worst = this->residentes[1];  //elitismo peor

    for(auto i: this->residentes){

        //nextGen.push_back(i);
        if (i.factible && !best.factible){
            best = i;
            std::cout << "encontro algo factible" ;
        }
        else if (!i.factible && best.factible){
            (void)0;
        }
        else{

            if (i.calidad < best.calidad){  //mayor calidad -- peor solucion

                best = i;
            }
            if (i.calidad > worst.calidad){  //mayor calidad -- peor solucion

                worst = i;
            }
        }
    }

    /*agregar mejor y peor a la siguiente generacion*/
    nextGen.push_back(best);
    nextGen.push_back(worst);

    int largo = (int) this->residentes.size();

    /*cruzar (10-2)/2 veces para obtener 8 hijos*/
    for (int i = 0; i < (largo-2)/2; i++) {

        /*obtener 1 padre y 1 madre*/
        /*2-torneo para padre*/
        int lugar1 = (std::rand()% (largo));
        int lugar2 = lugar1;

        while (lugar2 == lugar1) {

            lugar2 = (std::rand()% (largo));
        }

        if (this->residentes[lugar1].calidad > this->residentes[lugar2].calidad){

            lugar1 = lugar2;
        }
        Individuo padre = this->residentes[lugar1];

        /*2-torneo para madre*/
        int lugar3 = (std::rand()% (largo));;
        while (lugar3 == lugar1 || lugar3==lugar2 || lugar2 == lugar1) {

            lugar2 = (std::rand()% (largo));
            lugar3 = (std::rand()% (largo));
        }

        if (this->residentes[lugar2].calidad > this->residentes[lugar3].calidad){

            lugar2 = lugar3;
        }

        Individuo madre = this->residentes[lugar2];

        /*cruzar y agregar a la siguiente generacion*/
        cruzar(padre, madre);

        padre.mutar(this->maxRiesgo);
        madre.mutar(this->maxRiesgo);
        nextGen.push_back(padre);
        nextGen.push_back(madre);
    }

    /*actualizar generacion actual con la nueva generacion*/
    for (int i = 0; i < largo; i++) {

        this->residentes[i]=nextGen[i];
    }

};
