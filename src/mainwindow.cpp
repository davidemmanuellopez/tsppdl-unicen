#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <graph.h>
#include <iostream>
#include <fstream>
#include <math.h>
#include<tsplib.h>
#include <heuristics.h>
#include <QFuture>
#include <QtConcurrent/QtConcurrentRun>
#include <QThreadPool>
#include <QRunnable>

#include <QDebug>

#define bufSize = 512;


using namespace std;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QStringList heuristics;
    heuristics << "None" << "Node Swap" << "Node Relocate" << "Subtree Swap" << "Subtree Relocate" << "Perturbation" << "ATSP" << "Crossover";
    ui->comboBox->insertItems(0,heuristics);
    ui->comboBox_2->insertItems(0,heuristics);
    ui->comboBox_3->insertItems(0,heuristics);
    ui->comboBox_4->insertItems(0,heuristics);
    ui->comboBox_5->insertItems(0,heuristics);
    ui->comboBox_6->insertItems(0,heuristics);
    ui->comboBox_7->insertItems(0,heuristics);
    ui->comboBox_8->insertItems(0,heuristics);
    loaded = false;
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

void MainWindow::graficar()
{
    QProcess dotProcess(this);
    QStringList arg;
    arg << "-Tpng";
    dotProcess.start("dot",arg);
    if (!dotProcess.waitForStarted())
    {
        QMessageBox::critical(this,"Error","No se puedo lanzar el graficador dot");
        return;
    }

    GraphvizDotGenerator gdg;
    dotProcess.write(QByteArray (gdg.generar(adjacency,*arbol).c_str()));
    cout << gdg.generar(adjacency,*arbol).c_str();

    dotProcess.setReadChannel(QProcess::StandardOutput);

    QByteArray data;
    dotProcess.waitForReadyRead();
    do
    {
        qint64 buffSize = dotProcess.bytesAvailable();
        //char buffer[buffSize];
        char* buffer = new char[buffSize];
        //vector<char> bffer(buffSize);
        dotProcess.read(buffer,buffSize);
        data.append(buffer,buffSize);
        dotProcess.waitForReadyRead(100);
        delete[] buffer;
    } while ( dotProcess.bytesAvailable() );

    QPixmap qPixmap;
    qPixmap.loadFromData(data,"PNG");
    ui->label->setPixmap(qPixmap);

    dotProcess.kill();
    if (!dotProcess.waitForFinished())
    {
        QMessageBox::critical(this,"Error","No se puedo finalizar el graficador dot");
        return;
    }
    if ( arbol->tourLength()!=0 )
    {
        ostringstream is;
        is << "Solucion encontrada, costo: " << arbol->tourLength();
        QString qStatus=is.str().c_str();
        ui->statusBar->showMessage(qStatus);
    }
    else
        ui->statusBar->showMessage("Listo",1000);
}

void MainWindow::on_actionAbrir_triggered()
{
    //archivo .tsp
    QString fileName = QFileDialog::getOpenFileName(this,"Abrir","","*.tsp");
    ifstream file(fileName.toLatin1());
    qDebug() << "archivo" << fileName.toLatin1();
    //defino archivo .mtc
    string aux = fileName.toStdString().substr(fileName.lastIndexOf("/")+1);
    QString bef = aux.substr(0,aux.size()-4).c_str();
    ui->lE_Instance->setText(bef);
    aux = "/match_" + aux.substr(0,aux.size()-4)+".mtc";
    fileName = fileName.section('/',0,-2);//sustraigo el path del archivo cargado anteriormente
    fileName.append(aux.c_str());//le agrego al path el nombre del archivo
    ifstream mtcFile(fileName.toLatin1());


    //defino archivo .str
    aux = fileName.section('/',0,-2).toStdString();//sustraigo el path del archivo cargado anteriormente
    aux += "/ran_nn_" +fileName.section('_',-1).toStdString();
    aux = aux.substr(0,aux.size()-4) + ".str"; //agrego extension
    ifstream strFile(aux.c_str());

    if(!file.good()){
        string error = "Error al leer el archivo: ";
        QMessageBox::critical(this,"Error",error.c_str()+fileName.toLatin1());
    }
    else if(!mtcFile.good()){
        string error = "Error al leer el archivo: ";
        QMessageBox::critical(this,"Error",aux.c_str());
    }
    else if(!strFile.good()){
        string error = "Error al leer el archivo: "+ aux;
        QMessageBox::critical(this,"Error",error.c_str());
    }
    else{

       loaded = true;
       cantNodos = getCantNodos(file);

        //inic matriz adyacencia
        igraph_matrix_init(&adjacency,cantNodos,cantNodos);
        igraph_matrix_null(&adjacency);
        cargarMatriz(adjacency,file,cantNodos);

        //vectores de pares pickup & delivery
        igraph_vector_init(&pickupNodes,cantNodos);
        igraph_vector_init(&deliveryNodes,cantNodos);
        //inicializa vectores con valor discernible que indica que no aplica
        igraph_vector_fill(&pickupNodes,-1);
        igraph_vector_fill(&deliveryNodes,-1);
        cargarPares(mtcFile,pickupNodes,deliveryNodes,cantNodos);

        //con los datos cargados ya se puede instanciar el grafo
        grafo = new Graph(adjacency,pickupNodes,deliveryNodes);

        igraph_vector_t recorrido;
        igraph_vector_init(&recorrido,grafo->getDimension()+1);
        cargarRecorrido(strFile,recorrido,grafo);


        arbol = new Tree((grafo->getDimension()+1)/2,grafo); //instanciacion del arbol con la mitad de nodos que el grafo (p&d)

        arbol->initTree(recorrido,grafo);

        igraph_vector_destroy(&recorrido);

        file.close();
        mtcFile.close();
        strFile.close();

        ostringstream strs;
        strs << arbol->tourLength();
        string str = strs.str();
        QString bef = str.c_str();
        ui->lE_Before->setText(bef);       
    };

}

void MainWindow::on_pushButton_pressed()
{
    if (loaded){
        ostringstream strs;
        strs << arbol->tourLength();
        string str = strs.str();
        QString bef = str.c_str();
        ui->lE_Before->setText(bef);

        igraph_vector_t children;
        igraph_vector_init(&children,2);

        int iter = ui->sB_Total->value();
        QProgressDialog progress("Applying Heuristics. Please wait...", QString(), 0, iter*8, this);
        progress.setWindowModality(Qt::WindowModal);
        for(int i=0;i<iter;i++){
            runHeuristic(ui->comboBox->currentIndex(),ui->spinBox->value(),ui->sB_PopSize->value(),arbol);
            progress.setValue(8*i+1);
            runHeuristic(ui->comboBox_2->currentIndex(),ui->spinBox_2->value(),ui->sB_PopSize->value(),arbol);
            progress.setValue(8*i+2);
            runHeuristic(ui->comboBox_3->currentIndex(),ui->spinBox_3->value(),ui->sB_PopSize->value(),arbol);
            progress.setValue(8*i+3);
            runHeuristic(ui->comboBox_4->currentIndex(),ui->spinBox_4->value(),ui->sB_PopSize->value(),arbol);
            progress.setValue(8*i+4);
            runHeuristic(ui->comboBox_5->currentIndex(),ui->spinBox_5->value(),ui->sB_PopSize->value(),arbol);
            progress.setValue(8*i+5);
            runHeuristic(ui->comboBox_6->currentIndex(),ui->spinBox_6->value(),ui->sB_PopSize->value(),arbol);
            progress.setValue(8*i+6);
            runHeuristic(ui->comboBox_7->currentIndex(),ui->spinBox_7->value(),ui->sB_PopSize->value(),arbol);
            progress.setValue(8*i+7);
            runHeuristic(ui->comboBox_8->currentIndex(),ui->spinBox_8->value(),ui->sB_PopSize->value(),arbol);
        }

        ostringstream strs2;
        strs2 << arbol->tourLength();
        string str2 = strs2.str();
        QString bef2 = str2.c_str();
        ui->lE_After->setText(bef2);
    } else {
        QMessageBox::critical(this,"Error","You haven't loaded any tsp instance yet.");
    };

}



void MainWindow::on_actionSave_Tour_triggered()
{
    if (loaded){
        ofstream file("result.vns");
        igraph_vector_t tour;
        igraph_vector_init(&tour,grafo->getDimension()+1);
        arbol->getPath(tour);
        guardarRecorrido(file,tour,arbol->tourLength());
        igraph_vector_destroy(&tour);
        QMessageBox::information(this,"Save tour","The tour was successfully saved in result.vns");
    } else {
        QMessageBox::critical(this,"Error","You haven't loaded any tsp instance yet.");
    }
}

void MainWindow::on_pB_VNS_pressed()
{
    if (loaded){
        vns(arbol,ui->sB_PopSize->value(),ui->sB_Total->value());

        ostringstream strs2;
        strs2 << arbol->tourLength();
        string str2 = strs2.str();
        QString bef2 = str2.c_str();
        ui->lE_After->setText(bef2);
    } else {
        QMessageBox::critical(this,"Error","You haven't loaded any tsp instance yet.");
    }
}

void MainWindow::on_exit_button()
{
    cout << "exit" << endl;
}
void MainWindow::on_actionAcerca_de_triggered()
{
    QMessageBox::about(this,"Acerca de...","This software was created by \
David Lopez and Javier Marsicano as a final project for \
algorithms subject of\n UNCPBA University (Tandil - Argentina). \
                        \n The heuristics implemented are based on the paper 'The tree representation for TSPPDL' \
published by Yongquan Li, Andrew Lim, Qin Hu, Wee Chong Oon, Dejian Tu\n \
                       \nFor more information or suggestions:\
                       \nespectruz@gmail.com\
                       \njmarsican@gmail.com\
                       \nhttp://aydalgo2.alumnos.exa.unicen.edu.ar\
                       \nhttp://www.exa.unicen.edu.ar");
}

void MainWindow::on_pB_Draw_pressed()
{
    if (loaded){
        if (arbol->getDimension()<=25){
            arbol->PathtoFile("graphviz");
        } else {
            QMessageBox::critical(this,"Error","Can't draw. The instance is too large.");
        }
    } else {
        QMessageBox::critical(this,"Error","You haven't loaded any tsp instance yet.");
    }

}
