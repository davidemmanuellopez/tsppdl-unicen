#define non_imp 15
#include "list"
#include "tree.h"
#include "heuristics.h"
#include "vector"
#include <iostream>

using namespace std;

void vns(Tree* &arbol, int pop_size, int max_iter)
{
    Tree* bestsolution = new Tree(arbol);
    vector<Tree*> population(pop_size);

    for (int x=0;x<max_iter;x++)
    {
       // cout << "iteracion " << x  << ",costo "<< bestsolution->tourLength() << endl;
       // population
        for (int k=0;k<pop_size;k++)
        {
            Tree* t = new Tree(bestsolution);
            population[k]= t;
        };

    int j = 0;
    while (j< non_imp)
    {
        cout << "j: "<< j << endl;
        for (int k=0;k<pop_size;k++)
        {
            local_search(population[k]);
            atsp_operator(population[k]);
        };

        for (int i=0;i<pop_size;i++)
        {
            for (int j=0;j<pop_size;j++)
            {
                if (i!=j) crossover_operator(population[i],population[j]);
            };
        };
        //busco mejor sol en population
            double mcost = population[0]->tourLength();
            int ind = 0;
            for (int i=1;i<pop_size;i++)
            {
                if (population[i]->tourLength() < mcost)
                {
                    mcost = population[i]->tourLength();
                    ind = i;
                };
            };

            if (mcost < bestsolution->tourLength())
            {
                delete bestsolution;
                bestsolution = new Tree(population[ind]);
                j = 0;
            } else j++;

            //perturbation

            for (int k=0;k<pop_size;k++)
            {
                perturbation(population[k]);
            };

        };

    //nueva iteracion
    for (int k=0;k<pop_size;k++)
    {
        delete population[k];
    };


   };
delete arbol;
 arbol = bestsolution;
};
