#include <QtWidgets/QApplication>
#include "mainwindow.h"
#include <igraph.h>
int main(int argc, char *argv[])
{
    igraph_i_set_attribute_table(&igraph_cattribute_table);
   // srand(time(NULL));

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
