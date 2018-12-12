#ifndef LAB3_GRAPH_H
#define LAB3_GRAPH_H

#include <vector>
#include <map>

class Graph {
public:
    std::map<int, std::vector<float>> map;
    std::vector<std::vector<float>>map_for_cache;

    std::vector<std::vector<float>> cost_calculation();

    Graph() = default;

};


#endif //LAB3_GRAPH_H
