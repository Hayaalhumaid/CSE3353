cmake_minimum_required(VERSION 3.12)
project(Lab4)
set(CMAKE_CXX_STANDARD 14)
add_executable(Lab4 main.cpp TSPAlgorithm.cpp TSPAlgorithm.h Graph.cpp Graph.h Algorithms.h AlgoHandler.h TSPProto.cpp TSPProto.h AlgoHandler.cpp FileReader.cpp FileReader.h TabuAlgorithm.cpp TabuAlgorithm.h TabuProto.cpp TabuProto.h GAAlgorithm.cpp GAAlgorithm.h GAProto.cpp GAProto.h)