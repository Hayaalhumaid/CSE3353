#include <fstream>
#include <iostream>
#include "TabuProto.h"

TabuProto::~TabuProto() {
}

void TabuProto::exec() {
    auto t1 = std::chrono::high_resolution_clock::now();
    fin_pair_ = t.tabu_search(g, src);
    auto t2 = std::chrono::high_resolution_clock::now();
    time = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);
}

void TabuProto::out() {
    std::cout << name_string_type << std::endl;
    std::cout << "Cost: " << fin_pair_.first << std::endl;
    std::cout << "Path: ";
    for(int v : fin_pair_.second){
        std::cout << v << "->";
    }
    std::cout << std::endl << "Time: " << time.count() << " microseconds" << std::endl;

    std::ofstream output("data/output.txt", std::ios_base::app);
    output << name_string_type << std::endl;
    output << "Cost: " << fin_pair_.first << std::endl;
    output << "Path: ";
    for(int v : fin_pair_.second){
        output << v << "->";
    }
    output << std::endl << "Time: " << time.count() << " microseconds" << std::endl;
    output.close();
}