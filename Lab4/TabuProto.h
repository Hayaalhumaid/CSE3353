#ifndef LAB_TABUPROTO_H
#define LAB_TABUPROTO_H

#include <vector>
#include <chrono>
#include <string>
#include "Algorithms.h"
#include "Graph.h"
#include "TabuAlgorithm.h"


class TabuProto : public Algorithms {
private:
    Graph* g;
    TabuAlgorithm* t;
    std::string name_string_type = "Tabu Search";
    std::chrono::microseconds time;
    std::pair<float,std::deque<int>> fin_pair_;
    int src = 1;

public:
    TabuProto() = default;

    TabuProto(Graph* g){
        this->g = g;
        t = new TabuAlgorithm();
    }

    void exec();
    void out();

    ~TabuProto();

};


#endif //LAB_TABUPROTO_H
