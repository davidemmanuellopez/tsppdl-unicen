#include <heuristics.h>
#include <igraph.h>

struct Relocalization{
    int nodo;
    int pos;
    int padreDest;
    double costo;
};

void tryReloc(int nodo, int padre, Tree& t, Relocalization& best)
//prueba las distintas posibilidades de relocalizar al nodo como hijo de padre
{
    igraph_vector_t hijos;
    igraph_vector_init(&hijos,2);

    //primero pruebo como primer hijo
    t.insertF(padre,nodo);
    double costoActual = t.tourLength();
    if (costoActual < best.costo){ //si mejora guardo
        best.nodo = nodo;
        best.padreDest = padre;
        best.pos = -1;
        best.costo = costoActual;
    }
    t.remove(padre,nodo); //deshacer

    if (t.hasChildren(padre)){
        //ahora pruebo como hijo posterior a todos sus hermanos
        t.getChildren(hijos,padre);
        for(int pos=0; pos<(igraph_vector_size(&hijos)-1); pos++){ //por cada posicion que puedo insertar como hijo de nodo padre
            t.insert(padre,nodo,VECTOR(hijos)[pos]);
            costoActual = t.tourLength();
            if (costoActual < best.costo){ //si mejora guardo
                best.nodo = nodo;
                best.padreDest = padre;
                best.pos = VECTOR(hijos)[pos];
                best.costo = costoActual;
            }
            //Deshacer relocalizacion
            t.remove(padre,nodo);
        }    
    }
    igraph_vector_destroy(&hijos);
}

void subtree_relocate_operator(Tree* t)
{
    Relocalization best;
    best.costo = t->tourLength();

    for (int i=1; i<t->getDimension();i++){
        igraph_vector_t omitidos;
        igraph_vector_init(&omitidos,2);
        t->getComponent(omitidos,i);
        igraph_vector_sort(&omitidos); //ordeno vector de componente para poder aplicar busqueda binaria

        int padreOrig = t->getPadre(i);
        int posOrig = t->getAnt(i);
        t->remove(padreOrig,i); //lo descuelgo
        for (int p=0; p<t->getDimension(); p++) //por cada posible padre destino
            if (!igraph_vector_binsearch2(&omitidos,p)) //el nodo padre destino no debe pertenecer al subarbol a reubicar
                tryReloc(i,p,*t,best);

        //lo vuelvo a poner donde estaba originalmente para recuperar el estado inicial del arbol
        if (posOrig == -1)
            t->insertF(padreOrig,i);
        else
            t->insert(padreOrig,i,posOrig);

        igraph_vector_destroy(&omitidos);
    }

    //aplicar de forma efectiva la mejor relocalizacion encontrada
    if (t->tourLength() != best.costo)
    {
        t->remove(t->getPadre(best.nodo),best.nodo);
        if (best.pos == -1)
            t->insertF(best.padreDest,best.nodo);
        else
            t->insert(best.padreDest,best.nodo,best.pos);

    };
};
