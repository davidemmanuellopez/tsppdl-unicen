#include "graph.h"

/*
Graph::Graph(igraph_matrix_t m,ifstream& file)
{
    igraph_weighted_adjacency(&grafo,&m,IGRAPH_ADJ_UNDIRECTED,"peso");
    igraph_vector_fill(&pickupNodes,-1);
    igraph_vector_fill(&deliveryNodes,-1);
    cargarPares(file);
}*/

Graph::Graph(igraph_matrix_t& m)
{
    igraph_weighted_adjacency(&grafo,&m,IGRAPH_ADJ_UNDIRECTED,"peso");
   // igraph_vector_fill(&pickupNodes,-1);
    //igraph_vector_fill(&deliveryNodes,-1);

}

Graph::~Graph()
{
    igraph_destroy(&grafo);
};
float Graph::getEdgeWeight(int a, int b)
{
    igraph_integer_t eid;
    igraph_get_eid(&grafo,&eid,a,b,0);


   return igraph_cattribute_EAN(&grafo,"peso",eid);
};
void Graph::cargarPares(ifstream& file)
{
    char buffer[256];
    string str;
    int nodo;
    int par;
    file.getline(buffer,256); //ignoro la primer línea (depósito)
    while (!file.eof()){
        file.getline(buffer,256);
        str = buffer;
        nodo = atoi(str.substr(0,1).c_str());
        par = atoi(str.substr(5).c_str());
        if (str.substr(2,1)=="0")
            igraph_vector_set(&deliveryNodes,nodo,par);
        else
            igraph_vector_set(&deliveryNodes,nodo,par);

    }
}

bool Graph::isDelivery(int nodo){
    return igraph_vector_e(&deliveryNodes,nodo)!=-1;
}


void Graph::toGraphviz(string file)
{
    FILE* archivo;
    archivo = fopen("graphviz","w");
    igraph_write_graph_dot(&grafo,archivo);
};
