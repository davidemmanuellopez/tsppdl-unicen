#include "tsplib.h"
#include <stdlib.h>
#include <graph.h>
using namespace std;

int getCantNodos(ifstream& file){
    char buffer[256];
    file.getline(buffer,256);
    file.getline(buffer,256);
    file.getline(buffer,256); //ignoro las tres primeras líneas (NAME, COMMENT,TYPE)
    file.getline(buffer,256);
    string str = buffer;
    str = str.substr(12);
    int cantNodos = atoi(str.c_str());
    return cantNodos;
}

double dist(coord nodo1, coord nodo2){ //distancia eculidea entre dos coordenadas 2D
    return (sqrt(pow(nodo1.x - nodo2.x,2) + pow(nodo1.y - nodo2.y,2)));
}

//carga lamatriz de adyacencias desde el archivo ya posicionado en la línea 4
void cargarMatriz(igraph_matrix_t & m, ifstream& file, int cantNodos)
{
    coord aux[cantNodos];
    char buffer[256];
    file.getline(buffer,256);
    file.getline(buffer,256); //ignoro las líneas 5 y 6 (EDGE_WEIGHT_TYPE, NODE_COORD_SECTION)

    //cargo desde el archivo las coordenadas de los nodos en un arreglo

    int id;
    int i= 0;
    while ((i<cantNodos) && (!file.eof())){
        file.getline(buffer,256);
        if (!file.eof()){
            string str = buffer;
            sscanf(str.c_str(), "%i %i %i", &id, &aux[i].x, &aux[i].y);
            i++;
        }
    }

    //cargar distancias en matriz adyacencia
    for (int x= 0; x<cantNodos; x++){
        for(int y= x;y<cantNodos;y++){
            double valor=  dist(aux[x],aux[y]);
            igraph_real_t value = valor;
            igraph_matrix_set(&m,x,y,value);

              igraph_matrix_set(&m,y,x,value);

        }
    }
}

void cargarPares(ifstream& file,igraph_vector_t& pickupNodes,igraph_vector_t& deliveryNodes, int cantNodos)
{
    char buffer[256];
    string str;
    int nodo;
    int par;
    int isPickup;
    int contador = 0;
    file.getline(buffer,256); //ignoro la primer línea (depósito)
    while ((!file.eof())&&(contador<cantNodos-1)){
        file.getline(buffer,256);
        if (!file.eof()){
            str = buffer;
            sscanf(str.c_str(),"%i %i %i", &nodo,&isPickup,&par);
            if (nodo<cantNodos){
                if (isPickup == 0) //si es 0 -> delivery; sino pickup
                    igraph_vector_set(&deliveryNodes,nodo,par);
                else
                    igraph_vector_set(&pickupNodes,nodo,par);
            }
            else cout << "Se intento acceder al vector fuera de rango " << contador << " " << nodo << " " << cantNodos;
        }
        contador++;
    }
}

void cargarRecorrido(ifstream& file, igraph_vector_t& recorrido, Graph* grafo)
{
    char buffer[256];
    int cantidad = grafo->getDimension();

    int contador = 0;

    while (contador <=cantidad)
    {
        file.getline(buffer,256);
        string str = buffer;
        int nodo = atoi(str.c_str());
        VECTOR(recorrido)[contador] = nodo;
        contador++;
    };
};

void guardarRecorrido(ofstream& file, igraph_vector_t& recorrido, int cost)  //el archivo debe estar abierto
{
    for(int i=0; i<igraph_vector_size(&recorrido); i++){
        file << VECTOR(recorrido)[i] << endl;
    }
    file << "\n";
    file << cost;
}
