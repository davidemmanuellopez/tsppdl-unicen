#include <tree.h>
#include <list>
#include <heuristics.h>
#define limit 7

//http://www.bearcave.com/random_hacks/permute.html
void permute(Tree* t, int padre, const int start, igraph_vector_t& bestOrder,double& bestCost)
{
    igraph_vector_t children;
    igraph_vector_init(&children,2);
    t->getChildren(children,padre);

    if (start == (igraph_vector_size(&children))){
        double actual = t->tourLength();
        if (actual < bestCost){
            bestCost = actual;
            igraph_vector_update(&bestOrder,&children); //se guarda en bestOrder los valores de children - el mejor orden encontrado
        }
    }
    else{
            permute(t,padre,start+1,bestOrder,bestCost);

        for(int i=start+1; i<igraph_vector_size(&children); i++){

            t->subtreeSwap(VECTOR(children)[i],VECTOR(children)[start]);  //se intercambian los hijos
            permute(t,padre,start+1,bestOrder,bestCost);
            t->subtreeSwap(VECTOR(children)[i],VECTOR(children)[start]);  //se restablece el intercambio
        }
    }

    igraph_vector_destroy(&children);
}

void efectivizar(Tree* t, int padre, igraph_vector_t& bestOrder)
{
    for(int i=0;i<igraph_vector_size(&bestOrder);i++){
        t->remove(padre,VECTOR(bestOrder)[i]);
    }

    for(int i=0;i<igraph_vector_size(&bestOrder);i++){
        t->insertL(padre,VECTOR(bestOrder)[i]);
    }
}

void rai(Tree* t, int padre, igraph_vector_t& children)  //se asume que padre tiene hijos
{
    int tam = igraph_vector_size(&children);
    int i = rand() % (tam);
    int j = (rand() % (tam-i))+i;
    for (int c=i;c<=j;c++)
    {
        t->remove(padre,VECTOR(children)[c]);
    };
    list<int> nodop;
    nodop.push_front(padre);

    for(int c=i;c<=j;c++){
        bestlocation(t,VECTOR(children)[c],nodop);
    }
}

void atsp(Tree* t, int padre)
{
    if (t->hasChildren(padre))
    {
        igraph_vector_t children;
        igraph_vector_init(&children,2);

        t->getChildren(children,padre);
        double bestCost = t->tourLength();

        if(igraph_vector_size(&children)<=limit){
            permute(t,padre,0,children,bestCost);
            efectivizar(t,padre,children);//hacer que los hijos en el arbol tomen el orden de children
        }
        else
            rai(t,padre,children);
        igraph_vector_destroy(&children);
   };
};

void atsp_operator(Tree* t)
{
    for(int i=0;i<t->getDimension();i++){
        atsp(t,i);
    }
}
