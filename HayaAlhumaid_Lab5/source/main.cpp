#include <iostream>
#include "AlgoHandler.h"

int main() {
    remove("data/output.txt");
    AlgoHandler industry;
    industry.load_new();

	industry.select_algo(AlgoHandler::AlgoType::TABU);
	industry.run_algo();

	industry.select_algo(AlgoHandler::AlgoType::GENETIC);
	industry.run_algo();

	industry.select_algo(AlgoHandler::AlgoType::SA);
	industry.run_algo();

	industry.select_algo(AlgoHandler::AlgoType::PSO);
	industry.run_algo();

    return 0;
}