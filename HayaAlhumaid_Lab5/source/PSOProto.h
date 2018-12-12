#ifndef LAB5_PROPROTO_H
#define LAB5_PROPROTO_H

#include <chrono>
#include <string>
#include "Algorithms.h"
#include "PSOAlgorithm.h"

class PSOProto : public Algorithms {
private:
    Graph* g;
    PSOAlgorithm sa;

    std::string name_string_type = "Particle Swarm Optimisation";
    std::chrono::microseconds time;
    std::pair<float,std::vector<int>> fin_pair_;
    int source = 1;

public:
	PSOProto() = default;

	PSOProto(Graph* g){
        this->g = g;
    }

    void exec();
    void out();

    ~PSOProto();

};


#endif //LAB5_PROPROTO_H
