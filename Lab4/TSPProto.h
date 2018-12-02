
#ifndef LAB_TSPPROTO_H
#define LAB_TSPPROTO_H

#include <vector>
#include <chrono>
#include <string>
#include "Graph.h"
#include "TSPAlgorithm.h"
#include "Algorithms.h"

class TSPProto : public Algorithms{
private:
    std::vector<std::pair<float,std::vector<int>> (*)(Graph* g, int src)> algos;
    int type = 1;
    int src = 1;
    Graph* g;

    std::string name_string_type;
    std::chrono::microseconds time;
    std::pair<float,std::vector<int>> fin_pair_;
public:
    TSPProto() = default;

    TSPProto(Graph* g){
        this->g = g;
        algos.push_back(TSPAlgorithm::TSP_Naive);
        algos.push_back(TSPAlgorithm::TSPDynamic);
    }

    void sel(int);
    void exec();
    void out();
};


#endif //LAB_TSPPROTO_H
