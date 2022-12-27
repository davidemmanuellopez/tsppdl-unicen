#include "heuristicgenerator.h"

void HeuristicGenerator::execute(int iter, Tree* arbol){
    for (int i=0;i<iter;i++) heuristic(arbol);
}

Perturbation::Perturbation(){}

void Perturbation::heuristic(Tree* arbol){
    perturbation(arbol);
}

Perturbation::~Perturbation(){}



SubtreeRelocate::SubtreeRelocate(){};

void SubtreeRelocate::heuristic(Tree* arbol){
    subtree_relocate_operator(arbol);
}

SubtreeRelocate::~SubtreeRelocate(){};



SubtreeSwap::SubtreeSwap(){}

void SubtreeSwap::heuristic(Tree* arbol){
    subtree_swap_operator(arbol);
}

SubtreeSwap::~SubtreeSwap(){}

Atsp::Atsp(){};

void Atsp::heuristic(Tree *arbol){
    atsp_operator(arbol);
}

Atsp::~Atsp(){};



NodeRelocate::NodeRelocate(){}

void NodeRelocate::heuristic(Tree *arbol){
    multi_relocate_operator(arbol);
}

NodeRelocate::~NodeRelocate(){};



NodeSwap::NodeSwap(){}

void NodeSwap::heuristic(Tree* arbol){
    node_swap_operator(arbol);
}

NodeSwap::~NodeSwap(){}


CrossOver::CrossOver(Tree *arbol){ secondary = arbol;}

void CrossOver::heuristic(Tree* arbol){
    crossover_operator(arbol, secondary);
}

CrossOver::~CrossOver(){ delete secondary; }
