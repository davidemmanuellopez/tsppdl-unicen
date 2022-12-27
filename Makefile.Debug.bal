#############################################################################
# Makefile for building: tsppdl-unicen
# Generated by qmake (2.01a) (Qt 4.7.3) on: mar sep 13 19:26:38 2011
# Project:  tsppdl-unicen.pro
# Template: app
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DUNICODE -DQT_LARGEFILE_SUPPORT -DQT_GUI_LIB -DQT_CORE_LIB -DQT_THREAD_SUPPORT -DQT_NEEDS_QMAIN -DQT_NO_DYNAMIC_CAST
CFLAGS        = -g -Wall $(DEFINES)
CXXFLAGS      = -g -fexceptions -mthreads -Wall -fno-rtti $(DEFINES)
INCPATH       = -I'/usr/include/QtCore' -I'/usr/include/QtGui' -I'/usr/include' -I'igraph/include' -I'/usr/include/ActiveQt' -I'debug' -I'.' -I'/usr/share/qt/mkspecs/win32-g++'
LINK        =        g++
LFLAGS        =        -enable-stdcall-fixup -Wl,-enable-auto-import -Wl,-enable-runtime-pseudo-reloc -mthreads -Wl -Wl,-subsystem,windows
LIBS        =        -L'/usr/lib' -lmingw32 -lqtmaind -L/home/espectruz/tsppdl-unicen/igraph/lib -ligraph -lQtGuid -lQtCored 
QMAKE         = /usr/bin/qmake
IDC           = /usr/bin/idc.exe
IDL           = midl
ZIP           = zip -r -9
DEF_FILE      = 
RES_FILE      = 
COPY          = cp
COPY_FILE     = $(COPY)
COPY_DIR      = xcopy /s /q /y /i
DEL_FILE      = rm
DEL_DIR       = rmdir
MOVE          = mv
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir
INSTALL_FILE    = $(COPY_FILE)
INSTALL_PROGRAM = $(COPY_FILE)
INSTALL_DIR     = $(COPY_DIR)

####### Output directory

OBJECTS_DIR   = debug/

####### Files

SOURCES       = main.cpp \
		mainwindow.cpp \
		tree.cpp \
		graph.cpp \
		tsplib.cpp \
		multirelocate.cpp \
		nodeswap.cpp \
		subtreeswap.cpp \
		crossover.cpp \
		subtreeReloc.cpp \
		atsp.cpp \
		perturbation.cpp \
		thread.cpp \
		vns.cpp \
		localsearch.cpp debug/moc_mainwindow.cpp
OBJECTS       = debug/main.o \
		debug/mainwindow.o \
		debug/tree.o \
		debug/graph.o \
		debug/tsplib.o \
		debug/multirelocate.o \
		debug/nodeswap.o \
		debug/subtreeswap.o \
		debug/crossover.o \
		debug/subtreeReloc.o \
		debug/atsp.o \
		debug/perturbation.o \
		debug/thread.o \
		debug/vns.o \
		debug/localsearch.o \
		debug/moc_mainwindow.o
DIST          = 
QMAKE_TARGET  = tsppdl-unicen
DESTDIR        = debug/ #avoid trailing-slash linebreak
TARGET         = tsppdl-unicen.exe
DESTDIR_TARGET = debug/tsppdl-unicen.exe

####### Implicit rules

.SUFFIXES: .cpp .cc .cxx .C .c

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o $@ $<

####### Build rules

first: all
all: Makefile.Debug  $(DESTDIR_TARGET)

$(DESTDIR_TARGET): ui_mainwindow.h $(OBJECTS) 
	$(LINK) $(LFLAGS) -o $(DESTDIR_TARGET) object_script.tsppdl-unicen.Debug  $(LIBS)


qmake:  FORCE
	@$(QMAKE) -spec /usr/share/qt/mkspecs/win32-g++ -o Makefile.Debug tsppdl-unicen.pro

dist:
	$(ZIP) tsppdl-unicen.zip $(SOURCES) $(DIST) tsppdl-unicen.pro /usr/share/qt/mkspecs/qconfig.pri /usr/share/qt/mkspecs/modules/qt_webkit_version.pri /usr/share/qt/mkspecs/features/qt_functions.prf /usr/share/qt/mkspecs/features/qt_config.prf /usr/share/qt/mkspecs/features/exclusive_builds.prf /usr/share/qt/mkspecs/features/default_pre.prf /usr/share/qt/mkspecs/features/win32/default_pre.prf /usr/share/qt/mkspecs/features/debug.prf /usr/share/qt/mkspecs/features/debug_and_release.prf /usr/share/qt/mkspecs/features/default_post.prf /usr/share/qt/mkspecs/features/win32/default_post.prf /usr/share/qt/mkspecs/features/build_pass.prf /usr/share/qt/mkspecs/features/win32/stl.prf /usr/share/qt/mkspecs/features/win32/exceptions.prf /usr/share/qt/mkspecs/features/warn_on.prf /usr/share/qt/mkspecs/features/qt.prf /usr/share/qt/mkspecs/features/win32/thread.prf /usr/share/qt/mkspecs/features/moc.prf /usr/share/qt/mkspecs/features/win32/windows.prf /usr/share/qt/mkspecs/features/win32/rtti_off.prf /usr/share/qt/mkspecs/features/resources.prf /usr/share/qt/mkspecs/features/uic.prf /usr/share/qt/mkspecs/features/yacc.prf /usr/share/qt/mkspecs/features/lex.prf /usr/share/qt/mkspecs/features/include_source_dir.prf  HEADERS RESOURCES IMAGES SOURCES OBJECTIVE_SOURCES FORMS YACCSOURCES YACCSOURCES LEXSOURCES 

clean: compiler_clean 
	-$(DEL_FILE) debug/main.o debug/mainwindow.o debug/tree.o debug/graph.o debug/tsplib.o debug/multirelocate.o debug/nodeswap.o debug/subtreeswap.o debug/crossover.o debug/subtreeReloc.o debug/atsp.o debug/perturbation.o debug/thread.o debug/vns.o debug/localsearch.o debug/moc_mainwindow.o

distclean: clean
	-$(DEL_FILE) $(DESTDIR_TARGET)
	-$(DEL_FILE) Makefile.Debug

check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: debug/moc_mainwindow.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) debug/moc_mainwindow.cpp
debug/moc_mainwindow.cpp: tree.h \
		graph.h \
		mainwindow.h
	/usr/bin/moc.exe $(DEFINES) $(INCPATH) -D__GNUC__ -DWIN32 mainwindow.h -o debug/moc_mainwindow.cpp

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all: ui_mainwindow.h
compiler_uic_clean:
	-$(DEL_FILE) ui_mainwindow.h
ui_mainwindow.h: mainwindow.ui
	/usr/bin/uic.exe mainwindow.ui -o ui_mainwindow.h

compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_uic_clean 



####### Compile

debug/main.o: main.cpp mainwindow.h \
		tree.h \
		graph.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o debug/main.o main.cpp

debug/mainwindow.o: mainwindow.cpp mainwindow.h \
		tree.h \
		graph.h \
		ui_mainwindow.h \
		tsplib.h \
		heuristics.h \
		multioperation.h \
		thread.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o debug/mainwindow.o mainwindow.cpp

debug/tree.o: tree.cpp tree.h \
		graph.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o debug/tree.o tree.cpp

debug/graph.o: graph.cpp graph.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o debug/graph.o graph.cpp

debug/tsplib.o: tsplib.cpp tsplib.h \
		graph.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o debug/tsplib.o tsplib.cpp

debug/multirelocate.o: multirelocate.cpp heuristics.h \
		tree.h \
		graph.h \
		multioperation.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o debug/multirelocate.o multirelocate.cpp

debug/nodeswap.o: nodeswap.cpp heuristics.h \
		tree.h \
		graph.h \
		multioperation.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o debug/nodeswap.o nodeswap.cpp

debug/subtreeswap.o: subtreeswap.cpp heuristics.h \
		tree.h \
		graph.h \
		multioperation.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o debug/subtreeswap.o subtreeswap.cpp

debug/crossover.o: crossover.cpp tree.h \
		graph.h \
		heuristics.h \
		multioperation.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o debug/crossover.o crossover.cpp

debug/subtreeReloc.o: subtreeReloc.cpp heuristics.h \
		tree.h \
		graph.h \
		multioperation.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o debug/subtreeReloc.o subtreeReloc.cpp

debug/atsp.o: atsp.cpp tree.h \
		graph.h \
		heuristics.h \
		multioperation.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o debug/atsp.o atsp.cpp

debug/perturbation.o: perturbation.cpp heuristics.h \
		tree.h \
		graph.h \
		multioperation.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o debug/perturbation.o perturbation.cpp

debug/thread.o: thread.cpp thread.h \
		tree.h \
		graph.h \
		heuristics.h \
		multioperation.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o debug/thread.o thread.cpp

debug/vns.o: vns.cpp tree.h \
		graph.h \
		heuristics.h \
		multioperation.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o debug/vns.o vns.cpp

debug/localsearch.o: localsearch.cpp tree.h \
		graph.h \
		heuristics.h \
		multioperation.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o debug/localsearch.o localsearch.cpp

debug/moc_mainwindow.o: debug/moc_mainwindow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o debug/moc_mainwindow.o debug/moc_mainwindow.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

