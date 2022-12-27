#include<igraph.h>
#include<graph.h>
#ifndef TREE_H
#define TREE_H
#include <string.h>
class Tree
{
private:
    struct data
    {
        igraph_integer_t pickup;
        igraph_integer_t delivery;
    };

    data *elementsdata;

    int elements;
    int cnodes;
    int dimension;

    igraph_t arbol;
    igraph_t hermanos;
    igraph_vector_t primer_hijo;
    igraph_vector_t ultimo_hijo;
    igraph_vector_t costo_subarbol;
    Graph * original;


    void rmEdge(igraph_t& g, int a, int b);

    void updateCost(double delta, int nodo);

    void getEntorno(int &nodeant, int &nodesig, int n1);

public:
    Tree(int d,Graph* g);
    Tree(Tree* t);
    ~Tree();

    void PathtoFile(string archivo);

    int getPadre(int n);

    igraph_integer_t getPickup(int vertex);
    igraph_integer_t getDelivery(int vertex);

    void getHijos(igraph_vector_t *v, int vertex);
    int addVertex(int pick, int del);

    void setPickup(int nodo, int pick);
    void setDelivery(int nodo, int del);


    //nuevos

    void insert(int padre, int n, int a);
    void insertF(int padre, int n);
    void insertL(int padre, int n);
    void remove(int padre, int n);
    void nodeSwap(int n1, int n2);
    void subtreeSwap(int n1, int n2);

    int getSig(int n);
    int getAnt(int n);

    void getChildren(igraph_vector_t& v, int vertex);
    void toGraphviz(string file);
    void toGraphvizb(string file);

    void getPath(igraph_vector_t &vector);
    void initTree(igraph_vector_t& t, Graph* g);
    int getDimension();

    bool hasChildren(int vertex);

    void getComponent(igraph_vector_t& c, int padre);

    int getFChildren(int n);
    int getLChildren(int n);

    double tourLength();

};

#endif // TREE_H
