#include <iostream>
#include "AlgoHandler.h"

int main() {
    remove("data/output.txt");
    enum algo_tpes{TSP=1, TABU, GENETIC, LASTFACT};
    enum prob_type{NAIVE=1, DYNAMIC, LASTTYPE};
    AlgoHandler industry;
    industry.load_new();
    TabuProto* tabu;
    GAProto* gen_algorithm;
    tabu = (TabuProto*)(industry.generate(TABU));
    gen_algorithm = (GAProto*)(industry.generate(GENETIC));
    gen_algorithm->exec();
    gen_algorithm->out();

    delete tabu;
    delete gen_algorithm;

    return 0;
}