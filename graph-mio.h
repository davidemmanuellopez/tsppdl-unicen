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
    void cargarPares(ifstream& file);
public:

    Graph(igraph_matrix_t& m);
    ~Graph();
    float getEdgeWeight(int a, int b);
    bool isDelivery(int nodo);
    void toGraphviz(string file);
};

#endif // GRAPH_H
