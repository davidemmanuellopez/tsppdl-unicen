
#include <heuristics.h>
#include <tree.h>
#include <igraph.h>
#include <iostream>
#include "list"
#include "queue"
#include "multioperation.h"

void saveState(Tree* t, int n, MultiState &s)
{
    s.nodo = n;
    s.lbrother = t->getAnt(n);
    s.rbrother = t->getSig(n);
    s.lchildren = t->getFChildren(n);
    s.rchildren = t->getLChildren(n);
    s.padre = t->getPadre(n);

};

void desconectarMultirelocate(Tree* t, int nodo)
{
    int padre = t->getPadre(nodo);
    int ant = t->getAnt(nodo);
    t->remove(padre,nodo); //desconecto
    //conectamos sus hijos al abuelo


    igraph_vector_t hijos;
    igraph_vector_init(&hijos,2);

    if (t->hasChildren(nodo))
    {
    t->getChildren(hijos,nodo);
    int anttemp = ant;

    int i;
    if (ant == -1) {
            t->remove(nodo,VECTOR(hijos)[0]);
    t->insertF(padre,VECTOR(hijos)[0]);
    anttemp = VECTOR(hijos)[0];
    i=1;
    } else i=0;

    for (i;i<igraph_vector_size(&hijos);i++)
    {
        int hijo = VECTOR(hijos)[i];
        t->remove(nodo,hijo);
        t->insert(padre,hijo,anttemp);
        anttemp = hijo;
    };

    };
    igraph_vector_destroy(&hijos);
};


void ejecutarOperacion(Tree* t, MultiOperation op)
{
    int nodo = op.incial.nodo;
    desconectarMultirelocate(t,nodo);

    //conectar al nuevo padre
    int padrefinal;
    if (op.final.lbrother !=-1 && op.final.rbrother !=-1)
    {
        padrefinal = t->getPadre(op.final.rbrother);
    } else padrefinal = op.final.padre;

    if (op.final.lbrother !=-1)
    {
        t->insert(padrefinal,nodo,op.final.lbrother);
    } else t->insertF(padrefinal,nodo);

    //comienzo a pasar como hijos sus hermanos derechos
    int nright = t->getSig(nodo);
    //t->toGraphviz("debug");
    while (nright != op.final.rbrother)
    {
        int rm = nright;
        nright = t->getSig(nright);
        t->remove(padrefinal,rm);
        t->insertL(nodo,rm);

    };




    //
};

bool checkLeftBrother(int brother, igraph_vector_bool_t& pre,  igraph_vector_bool_t& post)
{
    return VECTOR(post)[brother];
};

bool checkRightBrother(int brother,  igraph_vector_bool_t& pre,  igraph_vector_bool_t& post)
{
    return VECTOR(pre)[brother];
};

bool checkLeftChildren(int children,  igraph_vector_bool_t& pre,  igraph_vector_bool_t& post)
{
        return VECTOR(pre)[children];
};

bool checkRightChildren(int children,  igraph_vector_bool_t& pre,  igraph_vector_bool_t& post)
{
        return VECTOR(post)[children];
};

bool checkFlags(MultiState s, igraph_vector_bool_t& pre, igraph_vector_bool_t& post)
{

    bool condicion = true;
    if (s.lbrother == -1)
     {
         condicion = condicion && VECTOR(pre)[s.padre]; //check padre
     } else condicion = condicion && checkLeftBrother(s.lbrother,pre,post);


    if (s.rbrother == -1)
     {
         condicion = condicion && (bool)(VECTOR(post)[s.padre]);
     } else condicion = condicion && checkRightBrother(s.rbrother,pre,post);


    if (s.lchildren !=-1 && s.rchildren!=-1)
{
        condicion = condicion && checkLeftChildren(s.lchildren,pre,post) && checkRightChildren(s.rchildren,pre,post);
    };

    condicion = condicion && VECTOR(pre)[s.nodo] && VECTOR(post)[s.nodo];



return condicion;
};





void MarkFlags(MultiState s, igraph_vector_bool_t& pre, igraph_vector_bool_t& post)
{


    if (s.lbrother == -1)
     {
         VECTOR(pre)[s.padre] = false; //check padre
     } else VECTOR(post)[s.lbrother] = false;



    if (s.rbrother == -1)
     {
         VECTOR(post)[s.padre] = false;
     } else VECTOR(post)[s.rbrother] = false;

    if (s.lchildren !=-1 && s.rchildren !=-1)
    {
       VECTOR(pre)[s.lchildren] = false;
       VECTOR(post)[s.rchildren] = false;
    };

    VECTOR(pre)[s.nodo] = false;
    VECTOR(post)[s.nodo] = false;
};

void relocations(Tree* t, int nodo, priority_queue<MultiOperation, vector<MultiOperation>, CompareOp> &cola, double costoinicial, MultiState estadoInicial)
{



    // guardamos el estado inicial




    int n = t->getDimension();


    int padre=0;

    while (padre < n) //  iteramos sobre la lista buscando nuevos padres
    {

        if (padre != nodo)
        {




        if (!t->hasChildren(padre)) //si no tiene hijo se inserta derecho
        {
                //hacer
                t->insertF(padre,nodo);

                double costo = t->tourLength(); //calculo costo

                //check
                if (costo < costoinicial)
                {
                    MultiState estadoFinal;
                    saveState(t,nodo,estadoFinal);

                    MultiOperation op;
                    op.incial = estadoInicial;
                    op.final = estadoFinal;
                    op.costo = costo;

                    cola.push(op);
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
            if (costo < costoinicial)
            {
                MultiState estadoFinal;
                saveState(t,nodo,estadoFinal);

                MultiOperation op;
                op.incial = estadoInicial;
                op.final = estadoFinal;
                op.costo = costo;

                cola.push(op);
            };



            for (int i=0;i<igraph_vector_size(&hijos);i++) //remuevo nodos que van desde el 0 hasta n (uno por uno)
            {
                int hijo = VECTOR(hijos)[i];
                t->remove(padre,hijo);

                t->insertL(nodo,hijo); // y los añado como hijos al "nodo"



                double costo = t->tourLength(); //calculo costo

                //check
                if (costo < costoinicial)
                {
                    MultiState estadoFinal;
                    saveState(t,nodo,estadoFinal);

                    MultiOperation op;
                    op.incial = estadoInicial;
                    op.final = estadoFinal;
                    op.costo = costo;

                    cola.push(op);
                };

            };

              // deshacemos la operacion
              t->remove(padre,nodo);


            for (int i=0;i<igraph_vector_size(&hijos);i++)
            {
                t->remove(nodo,VECTOR(hijos)[i]);
                t->insertL(padre,VECTOR(hijos)[i]);
            };




            //AHORA LO METEMOS EN EL MEDIO DE LOS HIJOS

            for (int h=0;h<igraph_vector_size(&hijos);h++) //se inserta despues del nodo h
            {
                t->insert(padre,nodo,VECTOR(hijos)[h]);
                double costo = t->tourLength(); //calculo costo

                //check
                if (costo < costoinicial)
                {
                    MultiState estadoFinal;
                    saveState(t,nodo,estadoFinal);

                    MultiOperation op;
                    op.incial = estadoInicial;
                    op.final = estadoFinal;
                    op.costo = costo;

                    cola.push(op);
                };

                for (int i=h+1;i<igraph_vector_size(&hijos);i++) //remuevo nodos h+1 hasta n
                {
                    t->remove(padre,VECTOR(hijos)[i]);
                    t->insertL(nodo,VECTOR(hijos)[i]);

                    double costo = t->tourLength(); //calcula costo

                    //check
                    if (costo < costoinicial)
                    {
                        MultiState estadoFinal;
                        saveState(t,nodo,estadoFinal);

                        MultiOperation op;
                        op.incial = estadoInicial;
                        op.final = estadoFinal;
                        op.costo = costo;

                        cola.push(op);
                    };



                };

                t->remove(padre,nodo);

                for (int i=h+1;i<igraph_vector_size(&hijos);i++)
                {
                    t->remove(nodo,VECTOR(hijos)[i]);
                    t->insertL(padre,VECTOR(hijos)[i]);
                };
            };

            igraph_vector_destroy(&hijos);
        };



        };
         padre++;

    };



};



void multi_relocate_operator(Tree* t)
{


    //variables para el almacenamiento del mejor relocate






    int n = t->getDimension();

    priority_queue<MultiOperation, vector<MultiOperation>, CompareOp> cola;



    for (int i=1;i<n;i++) // para cada elemento de la lista
    {
        int nodo = i;



            //desconectar
        int ant;
        int padreant;


        double costoinicial = t->tourLength();

        MultiState estadoInicial;
        saveState(t,nodo,estadoInicial);

        ant = t->getAnt(nodo); //desconectamos nodo
        padreant = t->getPadre(nodo);

        bool hadChildren = false;
        igraph_vector_t hijos;
        igraph_vector_init(&hijos,2);

        if (t->hasChildren(nodo))
        {
            hadChildren = true;
            t->getChildren(hijos,nodo);
        };

        desconectarMultirelocate(t,nodo);

        relocations(t,nodo,cola,costoinicial,estadoInicial);

        //conectar

        // conectar
        if (hadChildren)
        {
            for (int i=0;i<igraph_vector_size(&hijos);i++)
            {
                t->remove(padreant,VECTOR(hijos)[i]);
                t->insertL(nodo,VECTOR(hijos)[i]);
            };
        };

        igraph_vector_destroy(&hijos);

    if (ant == -1) t->insertF(padreant,nodo); else t->insert(padreant,nodo,ant);




};

    if (cola.size()> 0)
    {
        MultiOperation op = cola.top();
        ejecutarOperacion(t,op);

    };


    //definicion de estructuras para el 'multi'
    /*igraph_vector_bool_t pre;
    igraph_vector_bool_t post;

    igraph_vector_bool_init(&pre,n);
    igraph_vector_bool_init(&post,n);

    igraph_vector_bool_fill(&pre,true);
    igraph_vector_bool_fill(&post,true);



    while (cola.size() > 0)
       {


         //  cout << "costo:" << t->tourLength() << endl;


           MultiOperation op = cola.top();
           cola.pop();

           if (checkFlags(op.incial,pre,post) && checkFlags(op.final,pre,post))
           {
                   ejecutarOperacion(t,op);

                   MarkFlags(op.incial,pre,post);
                   MarkFlags(op.final,pre,post);

                   //<< "ejecuta" << endl;
            };
           // chequear que tenga hijos suficientes

       };
    //efectuar mejor relocation
*/


};


