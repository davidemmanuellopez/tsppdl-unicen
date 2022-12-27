#ifndef TSPLIB_H
#define TSPLIB_H
#include <igraph.h>
#include <istream>
#include <fstream>
#include <graph.h>
#include <iostream>

using namespace std;




struct coord
{
    int x;
    int y;
};

void cargarPares(ifstream& file,igraph_vector_t& pickupNodes,igraph_vector_t& deliveryNodes, int cantNodos);

void cargarMatriz(igraph_matrix_t & m, ifstream& file, int cantNodos);

double dist(coord nodo1, coord nodo2); //distancia eculidea entre dos coordenadas 2D

int getCantNodos(ifstream& file);

void cargarRecorrido(ifstream& file, igraph_vector_t& recorrido, Graph* grafo);

void guardarRecorrido(ofstream& file, igraph_vector_t& recorrido, int cost);

#endif // TSPLIB_H
