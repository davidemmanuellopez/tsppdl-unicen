cmake_minimum_required(VERSION 3.0)
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

add_subdirectory(igraph)
# Populate CMake variables with the sources

set (File_main_cpp ${PROJECT_SOURCE_DIR}/src/main.cpp)
set (File_mainwindow_cpp ${PROJECT_SOURCE_DIR}/src/mainwindow.cpp)
set (File_mainwindow_h ${PROJECT_SOURCE_DIR}/src/mainwindow.h)
set (File_mainwindow_ui  ${PROJECT_SOURCE_DIR}/src/mainwindow.ui)
set (File_graph_cpp ${PROJECT_SOURCE_DIR}/src/graph.cpp)
set (File_tree_cpp ${PROJECT_SOURCE_DIR}/src/tree.cpp)
set (File_subtreeReloc_cpp ${PROJECT_SOURCE_DIR}/src/subtreeReloc.cpp)
set (File_subtreeswap_cpp ${PROJECT_SOURCE_DIR}/src/subtreeswap.cpp)
set (File_nodeswap_cpp ${PROJECT_SOURCE_DIR}/src/nodeswap.cpp)
set (File_multirelocate_cpp ${PROJECT_SOURCE_DIR}/src/multirelocate.cpp)
set (File_crossover_cpp ${PROJECT_SOURCE_DIR}/src/crossover.cpp)
set (File_perturbation_cpp ${PROJECT_SOURCE_DIR}/src/perturbation.cpp)
set (File_atsp_cpp ${PROJECT_SOURCE_DIR}/src/atsp.cpp)
set (File_graphvizdotgenerator_cpp ${PROJECT_SOURCE_DIR}/src/graphvizdotgenerator.cpp)
set (File_vns_cpp ${PROJECT_SOURCE_DIR}/src/vns.cpp)
set (File_localsearch_cpp ${PROJECT_SOURCE_DIR}/src/localsearch.cpp)
set (File_heuristicgenerator_cpp ${PROJECT_SOURCE_DIR}/src/heuristicgenerator.cpp)
set (File_runner_cpp ${PROJECT_SOURCE_DIR}/src/runner.cpp)
set (File_tsplib_cpp ${PROJECT_SOURCE_DIR}/src/tsplib.cpp)

set (File_graph_h ${PROJECT_SOURCE_DIR}/src/graph.h)
set (File_tsplib_h ${PROJECT_SOURCE_DIR}/src/tsplib.h)
set (File_heuristics_h ${PROJECT_SOURCE_DIR}/src/heuristics.h)
set (File_multioperator_h ${PROJECT_SOURCE_DIR}/src/multioperation.h)
set (File_graphvizdotgenerator_h ${PROJECT_SOURCE_DIR}/src/graphvizdotgenerator.h)
set (File_heuristicgenerator_h ${PROJECT_SOURCE_DIR}/src/heuristicgenerator.h)

qt5_wrap_cpp(File_mainwindow_hdr_moc ${File_mainwindow_h})
qt5_wrap_ui (File_mainwindow_ui_moc  ${File_mainwindow_ui})


include_directories (${PROJECT_SOURCE_DIR}/src)

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


add_executable(tsppdl-unicen ${File_main_cpp})
target_link_libraries (tsppdl-unicen MyProjectLib)

