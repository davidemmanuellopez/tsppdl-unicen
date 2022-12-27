#ifndef HEURISTICGENERATOR_H
#define HEURISTICGENERATOR_H

#include <string>
#include <heuristics.h>
#include <tree.h>

class HeuristicGenerator
{
public:
    void execute(int iter, Tree* arbol);
    virtual void heuristic(Tree* arbol) = 0;
};

class Perturbation : public HeuristicGenerator
{
public:
    Perturbation();
    void heuristic(Tree* arbol);
    ~Perturbation();
};

class SubtreeRelocate : public HeuristicGenerator
{
public:
    SubtreeRelocate();
    void heuristic(Tree* arbol);
    ~SubtreeRelocate();
};

class SubtreeSwap : public HeuristicGenerator
{
public:
    SubtreeSwap();
    void heuristic(Tree* arbol);
    ~SubtreeSwap();
};

class Atsp : public HeuristicGenerator
{
public:
    Atsp();
    void heuristic(Tree *arbol);
    ~Atsp();
};

class NodeRelocate : public HeuristicGenerator
{
public:
    NodeRelocate();
    void heuristic(Tree *arbol);
    ~NodeRelocate();
};

class NodeSwap : public HeuristicGenerator
{
public:
    NodeSwap();
    void heuristic(Tree* arbol);
    ~NodeSwap();
};

class CrossOver : public HeuristicGenerator
{
public:
    CrossOver(Tree *arbol);
    void heuristic(Tree* arbol);
    ~CrossOver();
private:
    Tree* secondary; //este es será el arbol secundario
};

#endif // HEURISTICGENERATOR_H
