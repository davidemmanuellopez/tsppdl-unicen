#include <heuristics.h>
#include <igraph.h>
#include <iostream>
#include <queue>
#include <limits>
#include "list"

void bestlocation(Tree* t,int nodo, list<int> &padres)
{
    double best = std::numeric_limits<double>::max();
    MultiState estadoFinal;
    int n = t->getDimension();


    list<int>::iterator it = padres.begin();

    while (it!=padres.end()) //  iteramos sobre la lista buscando nuevos padres
    {
        int padre = *it;
        it++;


        if (!t->hasChildren(padre)) //si no tiene hijo se inserta derecho
        {
                //hacer
                t->insertF(padre,nodo);

                double costo = t->tourLength(); //calculo costo

                //check
                if (costo < best)
                {
                    best = costo;
                    saveState(t,nodo,estadoFinal);

                };

            //deshacer
            t->remove(padre,nodo);
        } else
        {

            igraph_vector_t hijos;
            igraph_vector_init(&hijos,2);

            t->getChildren(hijos,padre);


            //INSERTANDO NODO SOLO EN EL PRIMER LUGAR
            t->insertF(padre,nodo);
            double costo = t->tourLength(); //calculo costo

            //check
            if (costo < best)
            {
                best = costo;
                saveState(t,nodo,estadoFinal);
            };


/*
            for (int i=0;i<igraph_vector_size(&hijos);i++) //remuevo nodos que van desde el 0 hasta n (uno por uno)
            {
                int hijo = VECTOR(hijos)[i];
                t->remove(padre,hijo);

                t->insertL(nodo,hijo); // y los añado como hijos al "nodo"



                double costo = t->tourLength(); //calculo costo

                //check
                if (costo < best)
                {
                    best = costo;
                    saveState(t,nodo,estadoFinal);
                };

            };
*/
              // deshacemos la operacion
              t->remove(padre,nodo);

/*
            for (int i=0;i<igraph_vector_size(&hijos);i++)
            {
                t->remove(nodo,VECTOR(hijos)[i]);
                t->insertL(padre,VECTOR(hijos)[i]);
            };


*/

            //AHORA LO METEMOS EN EL MEDIO DE LOS HIJOS

            for (int h=0;h<igraph_vector_size(&hijos);h++) //se inserta despues del nodo h
            {
                t->insert(padre,nodo,VECTOR(hijos)[h]);
                double costo = t->tourLength(); //calculo costo

                //check
                if (costo < best)
                {
                    best = costo;
                    saveState(t,nodo,estadoFinal);
                };

                /*for (int i=h+1;i<igraph_vector_size(&hijos);i++) //remuevo nodos h+1 hasta n
                {
                    t->remove(padre,VECTOR(hijos)[i]);
                    t->insertL(nodo,VECTOR(hijos)[i]);

                    double costo = t->tourLength(); //calcula costo

                    //check
                    if (costo < best)
                    {
                        best = costo;
                        saveState(t,nodo,estadoFinal);
                    };



                };*/

                t->remove(padre,nodo);

                /*for (int i=h+1;i<igraph_vector_size(&hijos);i++)
                {
                    t->remove(nodo,VECTOR(hijos)[i]);
                    t->insertL(padre,VECTOR(hijos)[i]);
                };*/
            };

            igraph_vector_destroy(&hijos);
        };




    };

    //ejecutar best
    //conectar al nuevo padre
    int padrefinal;
    if (estadoFinal.lbrother !=-1 && estadoFinal.rbrother !=-1)
    {
        padrefinal = t->getPadre(estadoFinal.rbrother);
    } else padrefinal = estadoFinal.padre;

    if (estadoFinal.lbrother !=-1)
    {
        t->insert(padrefinal,nodo,estadoFinal.lbrother);
    } else t->insertF(padrefinal,nodo);

    //comienzo a pasar como hijos sus hermanos derechos
    int nright = t->getSig(nodo);

    while (nright != estadoFinal.rbrother)
    {
        int rm = nright;
        nright = t->getSig(nright);
        t->remove(padrefinal,rm);
        t->insertL(nodo,rm);

    };

};


void perturbation(Tree* t)
{
    int s = (rand() % (t->getDimension()-1))+1; // se selecciona un nodo raíz de subarbol aleatoriamente
   // cout << "s:" << s << endl;


    //se aislan todos los nodos del componente
    igraph_vector_t component;
    igraph_vector_init(&component,2);
    t->getComponent(component,s); //almaceno en el vector el conjunto de nodos del subarbol
    for (int i=0;i<igraph_vector_size(&component);i++)
    {
        int nodo = VECTOR(component)[i];
        t->remove(t->getPadre(nodo),nodo);
    };

    int cantNodos = igraph_vector_size(&component);

    for (int i=0; i<cantNodos; i++){ //por cada nodo del subarbol

        int posnodo = rand() % igraph_vector_size(&component);
        int nodo = VECTOR(component)[posnodo]; //selecciono aleatoriamente un nodo del subarbol
      //  cout << nodo << endl;
        igraph_vector_remove(&component,posnodo); //elimino del conjunto de nodos del subarbol el nodo seleccionado
        //colocar nodo en el arbol de tal manera que resulte en el recorrido mas corto


        //genero lista de padre
        igraph_vector_t componentp;
        igraph_vector_init(&componentp,2);
        t->getComponent(componentp,0);

        list<int> padres;
        for (int i=0;i<igraph_vector_size(&componentp);i++)
        {
            int p = VECTOR(componentp)[i];
            padres.push_front(p);
        };

        igraph_vector_destroy(&componentp);

       // t->toGraphviz("perturbation");
        bestlocation(t,nodo,padres);

    }

    igraph_vector_destroy(&component);

}

