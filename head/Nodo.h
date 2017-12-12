#ifndef NODO_H
#define NODO_H

class Nodo{
public:
    int numero; //id del nodo
    float x;    //posicion eje x
    float y;    //posicion eje y
    int demanda;    //demanda de este nodo

    Nodo(int i ,float ejeX, float ejeY, int d); //constructor
};
#endif
