
#include <heuristics.h>
#include <tree.h>
#include <igraph.h>
#include <iostream>
#include "list"
using namespace std;

void node_swap_operator(Tree* t){
    int dimension = t->getDimension();

    //pares que conforman el swap que obtiene el mejor costo
    int n1 = -1;
    int n2 = -1;

    double mejorCosto = t->tourLength(); //inicializo con el costo inicial
    double costoInicial = mejorCosto;


    for (int i = 1; i<dimension; i++){
        for (int j = i+1; j<dimension; j++){



            t->nodeSwap(i,j);
            double nuevoCosto = t->tourLength();
            if (nuevoCosto < mejorCosto){
                mejorCosto = nuevoCosto;
                n1 = i;
                n2 = j;
            }


            t->nodeSwap(i,j); //deshace el swap realizado
        }
    }

    if ((n1 != -1)&&(n2 != -1)){ //verifica si encontro una mejora
        t->nodeSwap(n1,n2);  //realiza el swap que obtiene el mejor costo
    }

}



