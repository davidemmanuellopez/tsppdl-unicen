#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <fstream>
#include <sstream>
#include <QMessageBox>
#include <stdio.h>
#include <stdlib.h>
#include <igraph.h>
#include <math.h>
#include <iostream>
#include <tree.h>
#include <graph.h>
using namespace std;

struct coord {int x; int y;};


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

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

float dist(coord nodo1, coord nodo2){ //distancia eculidea entre dos coordenadas 2D
    return (sqrt(pow(nodo1.x - nodo2.x,2) + pow(nodo1.y - nodo2.y,2)));
}

//carga lamatriz de adyacencias desde el archivo ya posicionado en la línea 4
void cargarMatriz(igraph_matrix_t & m, ifstream& file, int cantNodos)
{
    coord aux[cantNodos-1];
    char buffer[256];
    file.getline(buffer,256);
    file.getline(buffer,256); //ignoro las líneas 5 y 6 (EDGE_WEIGHT_TYPE, NODE_COORD_SECTION)

    //cargo desde el archivo las coordenadas de los nodos en un arreglo
    int i= 0;
    while ((i<cantNodos) && (!file.eof())){
        file.getline(buffer,256);
        string str = buffer;
        aux[i].x = atoi(str.substr(9,4).c_str());
        aux[i].y = atoi(str.substr(17,4).c_str());
        i++;
    }



    //cargar distancias en matriz adyacencia
    for (int x= 0; x<cantNodos; x++){
        for(int y= x;y<cantNodos;y++){
            igraph_real_t value = dist(aux[x],aux[y]);
            igraph_matrix_set(&m,x,y,value);
            if (x!=y){ //simetría
                igraph_matrix_set(&m,y,x,value);
            }
        }        
    }    
}

void MainWindow::on_actionAbrir_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,"Abrir","","*.tsp");
    ifstream file(fileName.toAscii());
    if(!file.good()){
        string error = "Error al leer el archivo: ";
        QMessageBox::critical(this,"Error",error.c_str()+fileName.toAscii());
    }


    int cantNodos = getCantNodos(file);
    //QMessageBox::critical(this,"Error",str.c_str());

    //inic matrix
    igraph_matrix_t adjacency;
    igraph_matrix_init(&adjacency,cantNodos,cantNodos);
    igraph_matrix_null(&adjacency);

    cargarMatriz(adjacency,file,cantNodos);

    Graph grafo(adjacency);

    grafo.toGraphviz("frf");
    //arbol = new Tree(cantNodos);

    //igraph_vector_destroy(&adj);
}


void MainWindow::on_pushButton_pressed()
{

/*
    igraph_vector_t camino;
    igraph_vector_init(&camino,10);
    VECTOR(camino)[0] =0;
    VECTOR(camino)[1] =0;
    VECTOR(camino)[2] =0;
    VECTOR(camino)[3] =0;
    VECTOR(camino)[4] =0;
    VECTOR(camino)[5] =0;
    VECTOR(camino)[6] =0;
    VECTOR(camino)[7] =0;
    VECTOR(camino)[8] =0;
    VECTOR(camino)[9] =0;*/
    /*Tree arbol(20);

    arbol.setPadre(1,0);
    arbol.setPadre(3,0);
    arbol.setPadre(2,0);
    arbol.setPadre(0,4);
    arbol.setPadre(5,1);
    igraph_vector_t adj;
    igraph_vector_init(&adj,4);

    //arbol.getHijos2(adj,0);
    cout << "hola:"  << igraph_vector_size(&adj);
    cout << "mostrar hijos:";

    for (int i=0;i<igraph_vector_size(&adj);i++)
    {
        cout << VECTOR(adj)[i] << '\n';
    };
        */

   /*
    //probando si subcomponent devuelve ordenado los nodos
    igraph_t grafo;
    igraph_empty(&grafo,40,1);

    igraph_add_edge(&grafo,0,2);
    igraph_add_edge(&grafo,2,3);
    igraph_add_edge(&grafo,3,1);


    igraph_vector_t vector;
    igraph_vector_init(&vector,20);

    igraph_subcomponent(&grafo,&vector,0,IGRAPH_OUT);

    cout << "componente:" << endl;

    for (int i=0; i<igraph_vector_size(&vector);i++)
    {
        cout << VECTOR(vector)[i] << endl;
    };*/
/*
    Tree arbol(20);

    arbol.insertF(0,1);
    arbol.insert(0,3,1);
    arbol.insertF(0,2);


   // arbol.remove(0,3);

    arbol.insertL(0,5);

    arbol.insertL(0,6);

    arbol.insertF(5,4);

    arbol.insertL(5,7);

    arbol.insertF(7,8);

      //  arbol.remove(5,7);


    igraph_vector_t vector;
    igraph_vector_init(&vector,20);


    arbol.getChildren(vector,5);

   cout << "hijos:" << endl;

    for (int i=0; i<igraph_vector_size(&vector);i++)
    {
        cout << VECTOR(vector)[i] << endl;
    };

        arbol.toGraphviz();

        cout << "padre de 4:" << arbol.getPadre(4) << endl;

*/
}

void MainWindow::cargarSolucionInicial(igraph_vector_t& sol)
{

};
