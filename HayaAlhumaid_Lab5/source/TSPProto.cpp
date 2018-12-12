#include <fstream>
#include <iostream>
#include "TSPProto.h"

void TSPProto::sel(int num_input) {
    switch (num_input){
        case 1:
            type = 1;
            name_string_type = "Naive";
            break;

        case 2:
            type = 2;
            name_string_type = "Dynamic";
            break;

        default:
            type = 0;
            std::cerr << "no algorithm selected." << std::endl;
            exit(EXIT_FAILURE);
    }
}

void TSPProto::exec() {
    auto t1 = std::chrono::high_resolution_clock::now();
    fin_pair_ = (*algos[type-1])(g, src);
    auto t2 = std::chrono::high_resolution_clock::now();
    time = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);
}

void TSPProto::out() {
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
}
