cmake_minimum_required(VERSION 2.8)
project(QtCmake)
set(CMAKE_CXX_STANDARD 11)
# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
#set(CMAKE_AUTOMOC ON)
# Create code from a list of Qt designer ui files
#set(CMAKE_AUTOUIC ON)

#set(CMAKE_PREFIX_PATH c:/Qt/Qt5/)

# Find the QtWidgets library
find_package(Qt5Widgets CONFIG REQUIRED)
find_package(igraph)
#find_package(Qt5MultimediaWidgets CONFIG REQUIRED)

add_subdirectory(igraph)
# Populate CMake variables with the sources

set (File_main_cpp ${PROJECT_SOURCE_DIR}/main.cpp)
set (File_mainwindow_cpp ${PROJECT_SOURCE_DIR}/mainwindow.cpp)
set (File_mainwindow_h ${PROJECT_SOURCE_DIR}/mainwindow.h)
set (File_mainwindow_ui  ${PROJECT_SOURCE_DIR}/mainwindow.ui)
set (File_graph_cpp ${PROJECT_SOURCE_DIR}/graph.cpp)
set (File_tree_cpp ${PROJECT_SOURCE_DIR}/tree.cpp)
set (File_subtreeReloc_cpp ${PROJECT_SOURCE_DIR}/subtreeReloc.cpp)
set (File_subtreeswap_cpp ${PROJECT_SOURCE_DIR}/subtreeswap.cpp)
set (File_nodeswap_cpp ${PROJECT_SOURCE_DIR}/nodeswap.cpp)
set (File_multirelocate_cpp ${PROJECT_SOURCE_DIR}/multirelocate.cpp)
set (File_crossover_cpp ${PROJECT_SOURCE_DIR}/crossover.cpp)
set (File_perturbation_cpp ${PROJECT_SOURCE_DIR}/perturbation.cpp)
set (File_atsp_cpp ${PROJECT_SOURCE_DIR}/atsp.cpp)
set (File_graphvizdotgenerator_cpp ${PROJECT_SOURCE_DIR}/graphvizdotgenerator.cpp)
set (File_vns_cpp ${PROJECT_SOURCE_DIR}/vns.cpp)
set (File_localsearch_cpp ${PROJECT_SOURCE_DIR}/localsearch.cpp)
set (File_heuristicgenerator_cpp ${PROJECT_SOURCE_DIR}/heuristicgenerator.cpp)
set (File_runner_cpp ${PROJECT_SOURCE_DIR}/runner.cpp)
set (File_tsplib_cpp ${PROJECT_SOURCE_DIR}/tsplib.cpp)

set (File_graph_h ${PROJECT_SOURCE_DIR}/graph.h)
set (File_tsplib_h ${PROJECT_SOURCE_DIR}/tsplib.h)
set (File_heuristics_h ${PROJECT_SOURCE_DIR}/heuristics.h)
set (File_multioperator_h ${PROJECT_SOURCE_DIR}/multioperation.h)
set (File_graphvizdotgenerator_h ${PROJECT_SOURCE_DIR}/graphvizdotgenerator.h)
set (File_heuristicgenerator_h ${PROJECT_SOURCE_DIR}/heuristicgenerator.h)

qt5_wrap_cpp(File_mainwindow_hdr_moc ${File_mainwindow_h})
qt5_wrap_ui (File_mainwindow_ui_moc  ${File_mainwindow_ui})


include_directories (${PROJECT_SOURCE_DIR})
#include_directories (${Qt5MultimediaWidgets_INCLUDE_DIRS})
#include_directories (/home/david/repos/igraph/include)
#include_directories (/home/david/repos/build_igraph_0.9.10/include)

add_library (MyProjectLib 
	${File_mainwindow_cpp}
	${File_mainwindow_h}
	${File_mainwindow_hdr_moc}
	${File_mainwindow_ui_moc}
	${File_graph_cpp}
	${File_tree_cpp}
	${File_subtreeReloc_cpp}
	${File_subtreeswap_cpp}
	${File_nodeswap_cpp}
	${File_multirelocate_cpp}
	${File_crossover_cpp}
	${File_perturbation_cpp}
	${File_atsp_cpp}
	${File_graphvizdotgenerator_cpp}
	${File_vns_cpp}
	${File_localsearch_cpp}
	${File_heuristicgenerator_cpp}
	${File_runner_cpp}
	${File_tsplib_cpp}

)


target_link_libraries (MyProjectLib Qt5::Widgets)
target_link_libraries(MyProjectLib igraph)




add_executable(MyProject ${File_main_cpp})
target_link_libraries (MyProject MyProjectLib)

