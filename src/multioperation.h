#ifndef MULTIOPERATION_H
#define MULTIOPERATION_H

struct MultiState
{
    int lbrother;
    int rbrother;
    int lchildren;
    int rchildren;
    int padre;
    int nodo;
};

struct MultiOperation

{
    double costo;
    MultiState incial;
    MultiState final;

};

class CompareOp {
public:
    bool operator()(MultiOperation& t1, MultiOperation& t2)
    {
        if (t2.costo < t1.costo) return true; else return false;
    }
};

#endif // MULTIOPERATION_H


