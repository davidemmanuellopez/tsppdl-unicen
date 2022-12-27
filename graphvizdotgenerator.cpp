#include "graphvizdotgenerator.h"
#include <cstdlib>
#include <string>
#include <sstream>

GraphvizDotGenerator::GraphvizDotGenerator()
{
}

string GraphvizDotGenerator::generar(const igraph_matrix_t &m, Tree& t)
{
    string dot = "digraph G {\n";

    dot+="rankdir=LR\n";

    // Agrego los nodos
    for ( unsigned i=0;i<igraph_matrix_nrow(&m);++i)
    {
        ostringstream o;
        o << i << ";" << endl;
        dot+=o.str();
    }

    // Agrego los arcos
    for (unsigned fila=0;fila<igraph_matrix_nrow(&m);++fila)
    {
        for (unsigned columna=0;columna<igraph_matrix_ncol(&m);++columna)
        {
            if ( MATRIX(m,fila,columna) < 9000 )   // Osea, que hay un arco, un costo tan grande no es arco
            {
                ostringstream o;
                o << fila << "->" << columna << " " << "[label=" << MATRIX(m,fila,columna);
                list< pair<int,int> > l;
                //l=t.getPath2();

                // Si el camino que nos pasan contiene este nodo lo marcamos de rojo
               /* for ( list< pair<int,int> >::iterator it=l.begin();it!=l.end();++it )
                    if ( *it==pair<int,int> (fila,columna) )
                        o << " color=red fontcolor=red style=bold";*/

                o << "];" << endl;
                dot+=o.str();
            }
        }
    }

    dot+="}\n";
    return dot;
}
