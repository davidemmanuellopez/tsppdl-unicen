#ifndef THREAD_H
#define THREAD_H
#include<QThread>
#include<QRunnable>
#include "tree.h"

class Thread: public QRunnable
{
public:
    Tree* arbol;
    Thread(Tree* t);
    void run();
};

#endif // THREAD_H
