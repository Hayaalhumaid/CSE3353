#ifndef LAB_TSP_H
#define LAB_TSP_H

#include <vector>
#include "Graph.h"

class TSPAlgorithm {
private:
    static float find_cost(Graph* g, int d1, int d2);
    static std::pair<float,std::vector<int>> TSPDynUtil(Graph* g, int source, int tempSrc, std::vector<int> vec, int& numIter);
public:
    static std::pair<float,std::vector<int>> TSP_Naive(Graph* g, int source);
    static std::pair<float,std::vector<int>> TSPDynamic(Graph* g, int source);

};

#endif
