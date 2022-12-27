#include "graph.h"
#include <iostream>

using namespace std;


Graph::Graph(igraph_matrix_t& m,igraph_vector_t& p, igraph_vector_t& d)
{
    igraph_weighted_adjacency(&grafo,&m,IGRAPH_ADJ_UNDIRECTED,"peso");
    igraph_vector_copy(&deliveryNodes,&d);
    igraph_vector_copy(&pickupNodes,&p);
    dimension = igraph_vector_size(&p);

}

Graph::Graph(Graph* g)
{
    igraph_copy(&grafo,&g->grafo);
    igraph_vector_copy(&deliveryNodes,&g->deliveryNodes);
    igraph_vector_copy(&pickupNodes,&g->pickupNodes);
    dimension = g->dimension;
};

Graph::~Graph()
{
    igraph_destroy(&grafo);
    igraph_vector_destroy(&deliveryNodes);
    igraph_vector_destroy(&pickupNodes);
};

int Graph::getDimension()
{
    return dimension;
};

double Graph::getEdgeWeight(int a, int b)
{
    if (a == b) return 0; //arreglar esto
    else
    {
        igraph_integer_t eid;
        igraph_get_eid(&grafo,&eid,a,b,0);
        return igraph_cattribute_EAN(&grafo,"peso",eid);

    };

};

bool Graph::isDelivery(int nodo){
    return igraph_vector_e(&deliveryNodes,nodo)!=-1;
}

void Graph::toGraphviz(string file)
{
    FILE* archivo;
    archivo = fopen(file.c_str(),"w");
    igraph_write_graph_dot(&grafo,archivo);
};

float Graph::tourLength(igraph_vector_t& tour){
    igraph_integer_t id;
    float acumulador = 0;


    int i = 0;
    igraph_integer_t current = VECTOR(tour)[i];
    igraph_integer_t next = VECTOR(tour)[i+1];


    while( current != -1 && next != -1)
     {
         igraph_get_eid(&grafo,&id,current,next,0);
         float aux= igraph_cattribute_EAN(&grafo,"peso",id);
         acumulador += aux;

         i++;

         current = VECTOR(tour)[i];
         next = VECTOR(tour)[i+1];
     };


    return acumulador;

}

int Graph::getPickup(int nodo)
{
    return VECTOR(deliveryNodes)[nodo];
    }

int Graph::getDelivery(int nodo)
{
    return VECTOR(pickupNodes)[nodo];

}

