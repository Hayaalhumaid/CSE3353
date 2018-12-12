#ifndef LAB_TSPGRAPH_H
#define LAB_TSPGRAPH_H

#include <vector>
#include <map>

class TSPGraph {
public:
    std::map<int, std::vector<float>> map;
    std::vector<std::vector<float>>map_for_cache;

    std::vector<std::vector<float>> cost_calculation();

    TSPGraph() = default;

};


#endif //LAB_TSPGRAPH_H
