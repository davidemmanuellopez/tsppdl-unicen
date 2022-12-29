#ifndef HEURISTICS_H
#define HEURISTICS_H
#include <tree.h>
#include "queue"
#include "multioperation.h"
#include "list"
#include <heuristicgenerator.h>
#include <iostream>

void subtree_swap_operator(Tree* t);
void node_swap_operator(Tree* t);
void multi_relocate_operator(Tree* t);
void crossover_operator(Tree* &t1, Tree *t2);
void subtree_relocate_operator(Tree* t);
void relocations(Tree* t, int nodo, priority_queue<MultiOperation, vector<MultiOperation>, CompareOp> &cola, double costoinicial, MultiState estadoInicial);
void ejecutarOperacion(Tree* t, MultiOperation op);
void perturbation(Tree* t);
void saveState(Tree* t, int n, MultiState &s);
void atsp(Tree* t, int padre);
void atsp_operator(Tree* t);
void bestlocation(Tree* t,int nodo, list<int> &padres);
void local_search(Tree* arbol);
void rai(Tree* t, int padre, igraph_vector_t& children);
void vns(Tree* &arbol, int pop_size, int max_iter);
void runHeuristic(int h,int iter, int popSize, Tree* &arbol);

#endif // HEURISTICS_H

