#include <iostream>
#include <fstream>
#include <string>

#include "Nodo.h"
#include "Poblacion.h"
#include "Individuo.h"

int main(int argc, char *argv[] )
{
    std::string s(argv[1]);
    //std::cout << "Ingrese archivo a analizar\n";
    //getline(std::cin, s);
    std::cout <<  s <<"\n";
    //std::string s = "Instancias-RCVRP/SET O/16.txt";
    //std::string s = "Instancias-RCVRP/SET V/RISK LEVEL 1.0/RISK LEVEL 1.0/22.txt";
    //std::string s = "Instancias-RCVRP/SET R/6_1_1.0.txt";
    Poblacion mundo = Poblacion(s);

    /*ocurre la magia*/
    for (int veces = 0; veces < 100; veces++) {

        mundo.cruzaMasiva();


    }

    /********* escribir en archivo *********/
    s+= ".out";
    std::cout << "========================================" <<  s <<"\n";
    std::ofstream file{s, std::ofstream::out};
    if (!file.good()){
        std::cout << "PROBLEMOM";
        return 1;
    }


    Individuo best = mundo.residentes[0];   //buscar al mejor

    for(auto i: mundo.residentes){
        if (i.calidad < best.calidad){  //mayor calidad -- peor solucion
            best = i;
        }
    }


    for(auto i: best.tour){
        std::cout << i.numero << "_";
    }
    std::cout << "\n";

    float recorrimiento = 0;
    for(auto i: best.miniDistancias){
        recorrimiento += i;
    }
    file << recorrimiento << "\n";
    std::cout << "\n";


    /*calculo la cantidad de autos*/
    int autos = 0;
    for(auto i: best.retorno){
        autos +=i;
        std::cout << i << "_";
    }
    std::cout << "\n";
    file << autos << "\n";

    /*veo las rutas, sus distancias y su riesgo*/
    std::string ruta = "0->";
    autos = 0;
    for (unsigned int j=1; j<best.tour.size(); j++){

        ruta+= std::to_string(best.tour[j].numero) ;
        ruta+= "->";

        if (best.retorno[j-1]==1){

            ruta+= "0";
            ruta+= "\n";
            file << best.miniDistancias[autos] << " " << best.miniRiesgos[autos] << " " << ruta;
            if (j < best.tour.size()-1){

                ruta = "0->";
            }
            autos++;
        }
    }
    file.close();

    std::cout << "\n" << best.factible << "\n";


    return 0;
}
