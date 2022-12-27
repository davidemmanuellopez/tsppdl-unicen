# -------------------------------------------------
# Project created by QtCreator 2011-07-09T11:57:10
# -------------------------------------------------
TARGET = tsppdl-unicen
TEMPLATE = app
SOURCES += main.cpp\
    mainwindow.cpp \
    graph.cpp \
    tree.cpp \
    tsplib.cpp \
    subtreeReloc.cpp \
    subtreeswap.cpp \
    nodeswap.cpp \
    multirelocate.cpp \
    crossover.cpp \
    perturbation.cpp \
    atsp.cpp \
    graphvizdotgenerator.cpp \
    vns.cpp \
    localsearch.cpp \
    heuristicgenerator.cpp \
    runner.cpp

INCLUDEPATH += "./igraph/include"

LIBS += -L/mnt/datos/nube/Dropbox/tsppdl-unicen/igraph/lib -ligraph

HEADERS += mainwindow.h\
    graph.h \
    tree.h \
    tsplib.h \
    heuristics.h \
    multioperation.h \
    graphvizdotgenerator.h \
    heuristicgenerator.h

FORMS += mainwindow.ui
