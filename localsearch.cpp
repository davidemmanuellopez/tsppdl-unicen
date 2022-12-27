#include "tree.h"
#include "heuristics.h"
#include <iostream>
void local_search(Tree* t)
{
    double costA;

    INICIO:


    costA = t->tourLength();
    node_swap_operator(t);
    if (t->tourLength() < costA) goto INICIO;

    costA = t->tourLength();
    subtree_swap_operator(t);
    if (t->tourLength() < costA) goto INICIO;


    costA = t->tourLength();
    subtree_relocate_operator(t);
    if (t->tourLength() < costA) goto INICIO;


    costA = t->tourLength();
    multi_relocate_operator(t);
    if (t->tourLength() < costA) goto INICIO;



};
