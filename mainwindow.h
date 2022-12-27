#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <igraph.h>
#include <tree.h>
#include <QProgressDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QProcess>
#include <graphvizdotgenerator.h>
#include <fstream>
#include <sstream>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void graficar();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;
    Tree *arbol;
    Graph *grafo;
    int cantNodos;
    bool loaded;
    igraph_matrix_t adjacency;
    igraph_vector_t pickupNodes;
    igraph_vector_t deliveryNodes;


private slots:
    void on_pB_Draw_pressed();
    void on_actionAcerca_de_triggered();
    void on_pB_VNS_pressed();
    void on_actionSave_Tour_triggered();
    void on_pushButton_2_pressed();
    void on_pushButton_pressed();
    void on_actionAbrir_triggered();
};

#endif // MAINWINDOW_H
