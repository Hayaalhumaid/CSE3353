#include "PSOProto.h"
#include <iostream>
#include <fstream>

PSOProto::~PSOProto() {
}

void PSOProto::exec() {
    auto t1 = std::chrono::high_resolution_clock::now();
	fin_pair_ = sa.simulate(g, source);
    auto t2 = std::chrono::high_resolution_clock::now();
	fin_pair_.second.insert(fin_pair_.second.begin(), 1);
    time = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);
}

void PSOProto::out() {
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