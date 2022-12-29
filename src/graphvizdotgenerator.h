#ifndef GRAPHVIZDOTGENERATOR_H
#define GRAPHVIZDOTGENERATOR_H

#include "tree.h"
#include "igraph.h"
#include "list"
#include <string>

using namespace std;

class GraphvizDotGenerator
{
public:
    GraphvizDotGenerator();
    string generar(const igraph_matrix_t &m, Tree& t);
};

#endif // GRAPHVIZDOTGENERATOR_H
