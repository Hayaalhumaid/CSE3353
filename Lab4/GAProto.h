#ifndef LAB4_GAPROTO_H
#define LAB4_GAPROTO_H

#include <chrono>
#include <string>
#include "Algorithms.h"
#include "GAAlgorithm.h"

class GAProto : public Algorithms {
private:
    Graph* g;
    GAAlgorithm* ga;

    std::string name_string_type = "Genetic Search";
    std::chrono::microseconds time;
    std::pair<float,std::vector<int>> fin_pair_;
    int source = 1;

public:
    GAProto() = default;

    GAProto(Graph* g){
        this->g = g;
        ga = new GAAlgorithm();
    }

    void exec();
    void out();

    ~GAProto();

};


#endif //LAB4_GAPROTO_H
