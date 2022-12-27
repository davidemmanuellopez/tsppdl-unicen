#include "thread.h"
#include <iostream>
#include "heuristics.h"

using namespace std;
void Thread::run()
{
    while (true)
    {
        /*int padre = arbol->getPadre(6);
        arbol->remove(padre,6);
        arbol->insertF(padre,6);
        */
        igraph_t grafo;
        igraph_empty(&grafo,10,1);
        igraph_destroy(&grafo);
    };
    //multi_relocate_operator(arbol);
};

Thread::Thread(Tree* t)
{
    arbol = t;
};
