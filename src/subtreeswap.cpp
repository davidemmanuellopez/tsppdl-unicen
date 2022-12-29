
#include <heuristics.h>
#include <tree.h>
#include <igraph.h>
#include <iostream>
#include "list"
using namespace std;


void subtree_swap_operator(Tree* t){

igraph_stack_t stack;
igraph_stack_init(&stack,t->getDimension());

int n1;
int n2;
double mejor = t->tourLength();
double inicial = mejor;

igraph_stack_push(&stack,0);

while (!igraph_stack_empty(&stack))
{
    int padre = igraph_stack_pop(&stack);
    //cout << "nodo padre:" << padre << endl;
    if (t->hasChildren(padre))
    {
            igraph_vector_t hijos;
            igraph_vector_init(&hijos,2);
            t->getChildren(hijos,padre);

            int chijos = igraph_vector_size(&hijos);
            igraph_vector_t* comp;
            comp = new igraph_vector_t[chijos];

            for (int i=0;i<chijos;i++)
            {
                igraph_vector_init(&comp[i],2);
                t->getComponent(comp[i],VECTOR(hijos)[i]);
                igraph_stack_push(&stack,VECTOR(hijos)[i]);
            };

            // tomo todos los pares de componentes

            for (int c1=0;c1<chijos;c1++)
            {
                for (int c2=c1+1;c2<chijos;c2++)
                {
                // ahora combino de a pares los componentes

                for (int e1=0;e1<igraph_vector_size(&comp[c1]);e1++)
                    {
                    for (int e2=0;e2<igraph_vector_size(&comp[c2]);e2++)
                    {
                        // par (e1,e2)

                       // cout << "par: (" << e1 << "," << e2 << ")" << endl;

                        int s1 = VECTOR(comp[c1])[e1];
                        int s2 = VECTOR(comp[c2])[e2];

                        if ( !t->hasChildren(s1) && !t->hasChildren(s2) )
                        {
                            t->subtreeSwap(s1,s2);
                            int c = t->tourLength();
                            if (c < mejor)
                            {
                                mejor = c;
                                n1 = s1;
                                n2 = s2;
                         };

                        t->subtreeSwap(s1,s2);

                    }

                    };
                };

                };
            };
    for (int i=0;i<chijos;i++)
    {
        igraph_vector_destroy(&comp[i]);
    };
    delete[] comp;

    igraph_vector_destroy(&hijos);
    };
};
igraph_stack_destroy(&stack);
//aplicar el mejor swap
if (mejor != inicial) t->subtreeSwap(n1,n2);
};


