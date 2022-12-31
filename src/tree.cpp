#include "tree.h"
#include <igraph.h>
#include <iostream>
#include <graph.h>
#include <math.h>


using namespace std;

Tree::Tree(int d,Graph* g)
{
    elementsdata = new data[d];
    elements = 0;
    dimension = d;
    cnodes = 1;
    igraph_empty(&arbol,d,1);
    igraph_empty(&hermanos,d,1);

    igraph_vector_init(&primer_hijo,d);
    igraph_vector_fill(&primer_hijo,-1);

    igraph_vector_init(&ultimo_hijo,d);
    igraph_vector_fill(&ultimo_hijo,-1);

    igraph_vector_init(&costo_subarbol,d);

    original = new Graph(g);
}

Tree::Tree(Tree* t)
{

    igraph_copy(&arbol,&t->arbol);
    igraph_copy(&hermanos,&t->hermanos);
    igraph_vector_copy(&primer_hijo,&t->primer_hijo);
    igraph_vector_copy(&ultimo_hijo,&t->ultimo_hijo);
    igraph_vector_copy(&costo_subarbol,&t->costo_subarbol);


    dimension = t->dimension;
    elements = t->elements;
    elementsdata = new data[dimension];
    cnodes = t->cnodes;
    for (int i=0;i<t->dimension;i++)
    {
        elementsdata[i] = t->elementsdata[i];
    };

    original = new Graph(t->original);
};
Tree::~Tree()
{
    delete elementsdata;
    igraph_destroy(&arbol);
    igraph_destroy(&hermanos);
    igraph_vector_destroy(&primer_hijo);
    igraph_vector_destroy(&ultimo_hijo);
    igraph_vector_destroy(&costo_subarbol);
    delete original;

};

int Tree::addVertex(int pick, int del)
{
    data d;

    d.pickup = pick;
    d.delivery = del;


    elementsdata[elements] = d;
    double costo;
    if (pick == del) costo = 0; else costo = original->getEdgeWeight(pick,del);
    VECTOR(costo_subarbol)[elements] = costo;
    elements++;
    return elements-1;
};


void Tree::rmEdge(igraph_t& g,int a, int b)
{
    igraph_integer_t eid;
    igraph_get_eid(&g,&eid,a,b,1,0);
    igraph_es_t arista;
    igraph_es_1(&arista,eid);
    igraph_delete_edges(&g,arista);
};

int Tree::getPadre(int n)
{
    igraph_vector_t vector;
    igraph_vector_init(&vector,2);
    igraph_vector_fill(&vector,-1);
    igraph_neighbors(&arbol,&vector,n,IGRAPH_IN);
    int padre = VECTOR(vector)[0];
    igraph_vector_destroy(&vector);
    return padre;
};
igraph_integer_t Tree::getPickup(int vertex)
{
    return elementsdata[vertex].pickup;
};

igraph_integer_t Tree::getDelivery(int vertex)
{
    return elementsdata[vertex].delivery;
};






int Tree::getSig(int n)
{
    igraph_vector_t nodos;
    igraph_vector_init(&nodos,2);
    igraph_vector_fill(&nodos,-1);
    igraph_neighbors(&hermanos,&nodos,n,IGRAPH_OUT);
    int sig = VECTOR(nodos)[0];
    igraph_vector_destroy(&nodos);
    return sig;

};

int Tree::getAnt(int n)
{

    igraph_vector_t nodos;
    igraph_vector_init(&nodos,2);
    igraph_vector_fill(&nodos,-1);
    igraph_neighbors(&hermanos,&nodos,n,IGRAPH_IN);
    int ant = VECTOR(nodos)[0];
    igraph_vector_destroy(&nodos);
    return ant;
};

void Tree::insert(int padre, int n, int a)
{
    cnodes++;


    if (VECTOR(ultimo_hijo)[padre] == a) insertL(padre,n); else
    {
        int b =getSig(a);
        igraph_add_edge(&arbol,padre,n); // agrego en el arbol
        rmEdge(hermanos,a,b);
        igraph_add_edge(&hermanos,a,n);
        igraph_add_edge(&hermanos,n,b);

        //calculo del gettourlength
        double costo = original->getEdgeWeight(getDelivery(a),getPickup(n));
        costo = costo + VECTOR(costo_subarbol)[n];
        costo = costo + original->getEdgeWeight(getDelivery(n),getPickup(b));

        double delta = original->getEdgeWeight(getDelivery(a),getPickup(b)) - costo;
        updateCost(delta,padre);
    };


};
void Tree::insertF(int padre, int n)
{

    cnodes++;



    int p_hijo = VECTOR(primer_hijo)[padre];
    if (p_hijo != -1)
    {
        igraph_add_edge(&hermanos,n,p_hijo);

              //calculo tourlength
        double costo = original->getEdgeWeight(getPickup(padre),getPickup(n));
        costo = costo + VECTOR(costo_subarbol)[n];
        costo = costo + original->getEdgeWeight(getDelivery(n),getPickup(p_hijo));

        double delta = original->getEdgeWeight(getPickup(padre),getPickup(p_hijo)) -costo;
        updateCost(delta,padre);

    } else
    {
        //si es el primer hijo

              //calculo tourlength
        double costo = original->getEdgeWeight(getPickup(padre),getPickup(n));
        costo = costo + VECTOR(costo_subarbol)[n];
        costo = costo + original->getEdgeWeight(getDelivery(n),getDelivery(padre));
        double delta = original->getEdgeWeight(getPickup(padre),getDelivery(padre)) - costo;
        updateCost(delta,padre);
        //calcular delta y hacer update
        VECTOR(ultimo_hijo)[padre] = n;
    };

    VECTOR(primer_hijo)[padre] = n;

    igraph_add_edge(&arbol,padre,n);
};
void Tree::insertL(int padre, int n)
{


    if (VECTOR(primer_hijo)[padre] == -1) insertF(padre,n); else
    {
        cnodes++;
        int ul_hijo = VECTOR(ultimo_hijo)[padre];
        igraph_add_edge(&hermanos,ul_hijo,n);

        //calculo tourlength
        double costo = original->getEdgeWeight(getDelivery(ul_hijo),getPickup(n));
        costo = costo + VECTOR(costo_subarbol)[n];
        costo = costo + original->getEdgeWeight(getDelivery(n),getDelivery(padre));

        double delta = original->getEdgeWeight(getDelivery(ul_hijo),getDelivery(padre)) - costo;
        updateCost(delta,padre);


        VECTOR(ultimo_hijo)[padre] = n;
        igraph_add_edge(&arbol,padre,n);
    };
};
void Tree::remove(int padre, int n)
{
    cnodes--;

if (VECTOR(primer_hijo)[padre]!=n && VECTOR(ultimo_hijo)[padre]!=n)
    {
    int ant = getAnt(n);
    int sig = getSig(n);

    //se elimina un nodo del medio
    double final = original->getEdgeWeight(getDelivery(ant),getPickup(sig));

    double inicial = original->getEdgeWeight(getDelivery(ant),getPickup(n));
    inicial = inicial + VECTOR(costo_subarbol)[n];
    inicial = inicial + original->getEdgeWeight(getDelivery(n),getPickup(sig));

    double delta = inicial - final;
    updateCost(delta,padre);

    rmEdge(hermanos,ant,n);
    rmEdge(hermanos,n,sig);
    igraph_add_edge(&hermanos,ant,sig);


} else
{
    if (VECTOR(primer_hijo)[padre] == VECTOR(ultimo_hijo)[padre])
    {
        //se elimina el unico hhijo
        //calculo del tourlength

        double inicial = original->getEdgeWeight(getPickup(padre),getPickup(n));
        inicial = inicial + VECTOR(costo_subarbol)[n];
        inicial = inicial + original->getEdgeWeight(getDelivery(n),getDelivery(padre));

        double final = original->getEdgeWeight(getPickup(padre),getDelivery(padre));
        double delta = inicial-final;
        updateCost(delta,padre);

        VECTOR(primer_hijo)[padre] = -1;
        VECTOR(ultimo_hijo)[padre] = -1;
    } else
    {
        if (VECTOR(primer_hijo)[padre] == n)
        {
            //si elimino el primero


            int sig = getSig(n);
            rmEdge(hermanos,n,sig);

            double inicial = original->getEdgeWeight(getPickup(padre), getPickup(n));
            inicial = inicial + VECTOR(costo_subarbol)[n];
            inicial = inicial + original->getEdgeWeight(getDelivery(n), getPickup(sig));

            double final = original->getEdgeWeight(getPickup(padre),getPickup(sig));

            double delta = inicial-final;
            updateCost(delta,padre);

            VECTOR(primer_hijo)[padre] = sig;
        } else
        {
            // si elimino el ultimo

            int ant = getAnt(n);
            rmEdge(hermanos,ant,n);

            double inicial = original->getEdgeWeight(getDelivery(ant), getPickup(n));
            inicial = inicial + VECTOR(costo_subarbol)[n];
            inicial = inicial + original->getEdgeWeight(getDelivery(n), getDelivery(padre));

            double final = original->getEdgeWeight(getDelivery(ant),getDelivery(padre));

            double delta = inicial-final;
            updateCost(delta,padre);

            VECTOR(ultimo_hijo)[padre] = ant;
        };
    };
};

    rmEdge(arbol,padre,n);

};

void Tree::getChildren(igraph_vector_t& v, int vertex)
    {

    igraph_subcomponent(&hermanos,&v,VECTOR(primer_hijo)[vertex],IGRAPH_OUT);
    
};

bool Tree::hasChildren(int vertex)
{
    return (VECTOR(primer_hijo)[vertex] != -1);
};


void Tree::toGraphviz(string file)
{
    FILE* archivo;
    archivo = fopen(file.c_str(),"w");
    igraph_write_graph_dot(&arbol,archivo);
    fclose(archivo);
};

void Tree::toGraphvizb(string file)
{
    FILE* archivo;
    archivo = fopen(file.c_str(),"w");
    igraph_write_graph_dot(&hermanos,archivo);
    fclose(archivo);
};

void Tree::setDelivery(int nodo, int del)
{
    elementsdata[nodo].delivery = del;
};

void Tree::setPickup(int nodo, int pick)
{
    elementsdata[nodo].pickup = pick;
};


void Tree::initTree(igraph_vector_t& t, Graph* g)
{
    igraph_stack_t stack;
    igraph_stack_init(&stack,igraph_vector_size(&t));

    addVertex(0,0);
    igraph_stack_push(&stack,0);


    int i = 1;
    igraph_integer_t nodoActual = VECTOR(t)[i];
    while (nodoActual != 0)
    {

        if (!g->isDelivery(nodoActual))
        {
            int id = addVertex(nodoActual,original->getDelivery(nodoActual));
            int padre = igraph_stack_top(&stack);
            insertL(padre,id);
            igraph_stack_push(&stack,id);
        } else
        {
            int id = igraph_stack_pop(&stack);
            //setDelivery(id,nodoActual);
        };
        i++;
        nodoActual = VECTOR(t)[i];
    };

    igraph_stack_destroy(&stack);

};

int Tree::getDimension()
{
    return dimension;
};

void Tree::getPath(igraph_vector_t &vector)
{
    igraph_stack_t stack;
    igraph_stack_init(&stack,dimension);

    igraph_vector_bool_t visited;
    igraph_vector_bool_init(&visited,dimension);
    igraph_vector_bool_fill(&visited,0);

    igraph_stack_push(&stack,0);
    int i=0;

    while (!igraph_stack_empty(&stack))
    {

        int nodo = igraph_stack_pop(&stack);
        if (VECTOR(visited)[nodo] == 0)
        {
            igraph_stack_push(&stack,nodo);



            if (hasChildren(nodo))
            {
                //get hijos
                igraph_vector_t hijos;
                igraph_vector_init(&hijos,10);
                getChildren(hijos,nodo);

                for (int h = igraph_vector_size(&hijos)-1;h>=0;h--)
                {
                    igraph_stack_push(&stack,VECTOR(hijos)[h]);

                };

                igraph_vector_destroy(&hijos);
            };



            VECTOR(visited)[nodo] = 1;
            VECTOR(vector)[i] = getPickup(nodo);
        } else
        {
            VECTOR(vector)[i] = getDelivery(nodo);
        };

         i++;

     };
    igraph_vector_bool_destroy(&visited);
    igraph_stack_destroy(&stack);
};

void Tree::getEntorno(int &nodeant, int &nodesig, int n1)
{

    if (getAnt(n1) !=-1 && getSig(n1)!=-1)
    {
        nodeant = getDelivery(getAnt(n1));
        nodesig = getPickup(getSig(n1));

    } else
    {

        if (getAnt(n1) == -1 && getSig(n1) == -1)
        {

            nodeant = getPickup(getPadre(n1));
            nodesig = getDelivery(getPadre(n1));

        } else
        {
            if (getAnt(n1) == -1)
            {
                nodeant = getPickup(getPadre(n1));
                nodesig = getPickup(getSig(n1));

            };

            if (getSig(n1) == -1)
            {
                nodeant = getDelivery(getAnt(n1));
                nodesig = getDelivery(getPadre(n1));

            };
        };

    };

};
void Tree::nodeSwap(int n1, int n2)
{

    //almaceno posiciones
    int padren1 = getPadre(n1);
    int padren2 = getPadre(n2);
    int antn1 = getAnt(n1);
    int antn2 = getAnt(n2);

    //desconecto nodos
    remove(padren1,n1);
    remove(padren2,n2);

    //desconecto e intercambiar hijos

    igraph_vector_t hijosn1;
    igraph_vector_init(&hijosn1,0);

    igraph_vector_t hijosn2;
    igraph_vector_init(&hijosn2,0);

    if (hasChildren(n1))
    {
        getChildren(hijosn1,n1);
    };

    if (hasChildren(n2))
    {
        getChildren(hijosn2,n2);
    };

    for (int i=0;i<igraph_vector_size(&hijosn1);i++)
    {
        int hijo = VECTOR(hijosn1)[i];
        remove(n1,hijo);
        insertL(n2,hijo);
    };

    for (int i=0;i<igraph_vector_size(&hijosn2);i++)
    {
        int hijo = VECTOR(hijosn2)[i];
        remove(n2,hijo);
        insertL(n1,hijo);
    };

    //reinsertar nodos

    if (n1 == padren2 || n2 == padren1)
    {
        if (n1 == padren2)
        {
            padren2 = n2;
        } else
        {
        //n2 == padren1
        padren1 = n1;
        };
    };


    bool primeron1 = true;

    if (antn1 == n2 || antn2 ==  n1)
    {
        if (antn1 == n2)
        {
            antn1 = n1;
            primeron1 = true;
        } else
        {
            //antn2 == n1
            antn2 = n2;
            primeron1 = false;
        };
    };


     if (!primeron1)
     {
         if (antn1!=-1) insert(padren1,n2,antn1); else insertF(padren1,n2);
         if (antn2!=-1) insert(padren2,n1,antn2); else insertF(padren2,n1);

     } else
     {

         if (antn2!=-1) insert(padren2,n1,antn2); else insertF(padren2,n1);
         if (antn1!=-1) insert(padren1,n2,antn1); else insertF(padren1,n2);

     };
    //efecuar intercambio











};

void Tree::subtreeSwap(int n1, int n2)
{
    //hardcode
    int antn1 = getAnt(n1);
    int pn1 = getPadre(n1);
    int antn2 = getAnt(n2);
    int pn2 = getPadre(n2);


   if (antn1 == n2 || antn2 == n1)
    {
       if (antn1 == n2){
        remove(pn1,n2);
        insert(pn1,n2,n1);
    } else {
        remove(pn2,n1);
        insert(pn1,n1,n2);
    };
   } else
   {

    remove(pn1,n1);
    remove(pn2,n2);

    if (antn1 == -1)
    {
        insertF(pn1,n2);
    } else insert(pn1,n2,antn1);

    if (antn2 == -1)
    {
        insertF(pn2,n1);
    } else

    {
         insert(pn2,n1,antn2);
    };



};
};

void Tree::getComponent(igraph_vector_t& c, int padre)
{
        igraph_subcomponent(&arbol,&c,padre,IGRAPH_OUT);
};

double Tree::tourLength(){

    double a = VECTOR(costo_subarbol)[0];

 return floor(a);

/*
    igraph_vector_t tour;
    igraph_vector_init(&tour, (dimension+2)*2);
    igraph_vector_fill(&tour,-1);
    getPath(tour);


    toGraphviz("debug");
    double tourcost = original->tourLength(tour);
    igraph_vector_destroy(&tour);


   // cout << "Costo 1:" << tourcost << endl;
    //cout << "Costo 2:" << VECTOR(costo_subarbol)[0] << endl;
return tourcost;*/

}



int Tree::getFChildren(int n)
{
    return VECTOR(primer_hijo)[n];
};

int Tree::getLChildren(int n)
{
    return VECTOR(ultimo_hijo)[n];
};


void Tree::updateCost(double delta, int n)
{
    VECTOR(costo_subarbol)[n] -= delta;
    if (getPadre(n) != -1) updateCost(delta,getPadre(n));
};

void Tree::PathtoFile(string archivo)
{
    igraph_vector_t tour;
    igraph_vector_init(&tour, (dimension+2)*2);
    igraph_vector_fill(&tour,-1);
    getPath(tour);

    igraph_t grafo;
    igraph_empty(&grafo,dimension*2-1,1);

    int i = 0;
    igraph_integer_t current = VECTOR(tour)[i];
    igraph_integer_t next = VECTOR(tour)[i+1];


    while( current != -1 && next != -1)
     {

         igraph_add_edge(&grafo,current,next);

         i++;

         current = VECTOR(tour)[i];
         next = VECTOR(tour)[i+1];
     };


    //to file


    FILE* file;
    file = fopen(archivo.c_str(),"w");
    igraph_write_graph_dot(&grafo,file);
    fclose(file);
    igraph_destroy(&grafo);

};
