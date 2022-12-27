#ifndef GRAPH_H
#define GRAPH_H
#include <igraph.h>
#include <fstream>
#include <cstdlib>
using namespace std;
class Graph
{
private:
    igraph_t grafo;
    igraph_vector_t pickupNodes;
    igraph_vector_t deliveryNodes;
    int dimension;
public:

    Graph(Graph* g);
    Graph(igraph_matrix_t& m,igraph_vector_t& p, igraph_vector_t& d);
    ~Graph();
    double getEdgeWeight(int a, int b);
    bool isDelivery(int nodo);
    void toGraphviz(string file);
    int getDimension();
    float tourLength(igraph_vector_t& tour);
    int getDelivery(int nodo);
    int getPickup(int nodo);

};

#endif // GRAPH_H
