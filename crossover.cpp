#include<tree.h>
#include<math.h>
#include "heuristics.h"
//funciona
void crossover_operator(Tree* &t1, Tree *t2)
{
    Tree* bak = new Tree(t1);
//selecionar nodo ramdom de T1
    int x =(rand() % (t1->getDimension()-1))+1;

    // hallar subarbol y eliminar nodos

    igraph_vector_t nodos;
    igraph_vector_init(&nodos,2);

    t1->getComponent(nodos,x);

    for (int i=0;i<igraph_vector_size(&nodos);i++)
    {
        //eliminar del padre
        int nodo = VECTOR(nodos)[i];
         int padre = t1->getPadre(nodo);
         t1->remove(padre,nodo);
    };

   // insertar nodo por nodo en T1

    for (int i=0;i<igraph_vector_size(&nodos);i++)
    {
        int nodo = VECTOR(nodos)[i];
        int padre = t2->getPadre(nodo);

        t1->insertF(padre,nodo);
        atsp(t1,padre);
    };

    if (t1->tourLength() < bak->tourLength())
    {
        delete bak;
    } else
    {
        delete t1;
        t1 = bak;
    };
};
