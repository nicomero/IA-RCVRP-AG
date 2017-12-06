#include <iostream>
#include <fstream>
#include <string>

#include "Nodo.h"

int main(void)
{

    Nodo santiago = Nodo(0, 1.0, 1.0, 4);


    std::cout << "Hola " << santiago.numero;


    return 0;
}
