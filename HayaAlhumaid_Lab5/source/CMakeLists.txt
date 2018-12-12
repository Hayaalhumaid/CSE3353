cmake_minimum_required(VERSION 3.12)
project(Lab5)
set(CMAKE_CXX_STANDARD 14)
add_executable(Lab5 main.cpp TSPAlgorithm.cpp TSPAlgorithm.h Graph.cpp Graph.h Algorithms.h AlgoHandler.h TSPProto.cpp TSPProto.h AlgoHandler.cpp FileReader.cpp FileReader.h TabuAlgorithm.cpp TabuAlgorithm.h TabuProto.cpp TabuProto.h GAAlgorithm.cpp GAAlgorithm.h GAProto.cpp GAProto.h SAAlgorithm.cpp SAAlgorithm.h SAProto.cpp SAProto.h PSOAlgorithm.cpp PSOAlgorithm.h PSOProto.cpp PSOProto.h)