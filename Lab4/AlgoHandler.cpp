#include "AlgoHandler.h"
#include <iostream>
#include <fstream>

void AlgoHandler::load_new() {
    f->load_new();

    for(int i = 0; i < f->file.size(); ++i) {
        g->map[stoi(f->file[i][0])].operator=({stof(f->file[i][1]), stof(f->file[i][2]), stof(f->file[i][3])});
    }

    g->cost_calculation();
}

Algorithms* AlgoHandler::generate(int input) {
    if(input==1){
        return new TSPProto(g);
    }
    else if(input == 2){
        return new TabuProto(g);
    }
    else if(input == 3){
        return new GAProto(g);
    }
    else{
        std::cout << "Error on generate" << std::endl;
        exit(EXIT_FAILURE);
    }
}

AlgoHandler::~AlgoHandler() {
    if(g != nullptr)
        delete g;
    g = nullptr;
}
