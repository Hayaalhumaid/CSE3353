#ifndef LAB_ALGOHANDLER_H
#define LAB_ALGOHANDLER_H

#include "TSPProto.h"
#include "TabuProto.h"
#include "GAProto.h"
#include "Graph.h"
#include "FileReader.h"

class AlgoHandler {
private:
    Graph* g;
    FileReader* f;
public:
    AlgoHandler(){
        g = new Graph();
        f = new FileReader();
    }
    ~AlgoHandler();
    void load_new();
    Algorithms* generate(int);

};

#endif //LAB_ALGOHANDLER_H
