#include "tree.h"
#include "heuristics.h"
using namespace std;

void runHeuristic(int h,int iter, int popSize, Tree* &arbol){

   Tree* bestsolution = new Tree(arbol);
   vector<Tree*> population(arbol->getDimension());

    for (int k=0;k<popSize;k++)
    {
         Tree* t = new Tree(bestsolution);
         population[k]= t;
    }

    HeuristicGenerator * algoritmo;
    switch (h) {
    case 0:
        break;
    case 1:
        algoritmo = new NodeSwap();
        for (int k=0;k<popSize;k++)
        {
            algoritmo->execute(iter,population[k]);
        }
        break;
    case 2:
        algoritmo = new NodeRelocate();
        for (int k=0;k<popSize;k++)
        {
            algoritmo->execute(iter,population[k]);
        }
        break;
    case 3:
        algoritmo = new SubtreeSwap();
        for (int k=0;k<popSize;k++)
        {
            algoritmo->execute(iter,population[k]);
        }
        break;
    case 4:
        algoritmo = new SubtreeRelocate();
        for (int k=0;k<popSize;k++)
        {
            algoritmo->execute(iter,population[k]);
        }
        break;
    case 5:
        algoritmo = new Perturbation();
        for (int k=0;k<popSize;k++)
        {
            algoritmo->execute(iter,population[k]);
        }
        break;
    case 6:
        algoritmo = new Atsp();
        for (int k=0;k<popSize;k++)
        {
            algoritmo->execute(iter,population[k]);
        }
        break;
     case 7:
        for (int i=0;i<popSize;i++)
        {
            algoritmo = new CrossOver(population[i]);
            for (int j=0;j<popSize;j++)
            {
                if (i!=j) crossover_operator(population[j],population[i]);
            };
        };

    }
    //busco mejor sol en population
        double mcost = population[0]->tourLength();
        int ind = 0;
        for (int i=1;i<popSize;i++)
        {
            if (population[i]->tourLength() < mcost)
            {
                mcost = population[i]->tourLength();
                ind = i;
            };
        };

        delete arbol;
        arbol = new Tree(population[ind]);
}
