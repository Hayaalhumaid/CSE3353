#ifndef LAB5_SAPROTO_H
#define LAB5_SAPROTO_H

#include <chrono>
#include <string>
#include "Algorithms.h"
#include "SAAlgorithm.h"

class SAProto : public Algorithms {
private:
    Graph* g;
    SAAlgorithm sa;

    std::string name_string_type = "Simulated Annealing";
    std::chrono::microseconds time;
    std::pair<float,std::vector<int>> fin_pair_;
    int source = 1;

public:
    SAProto() = default;

    SAProto(Graph* g){
        this->g = g;
    }

    void exec();
    void out();

    ~SAProto();

};


#endif //LAB5_SAPROTO_H
