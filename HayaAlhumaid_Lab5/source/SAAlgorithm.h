#ifndef LAB5_SAALGORITHM_H
#define LAB5_SAALGORITHM_H

#include <deque>
#include <vector>
#include "Graph.h"
#include <random>

class SAAlgorithm {
private:
	std::random_device rd;
	std::mt19937 gen{ rd() };

	float temperature;
	std::pair<float, std::vector<int>> best_tour;

	float p_function(float, float, float);
	float path_cost_get(Graph *, const std::vector<int>&, int);

public:
    SAAlgorithm() = default;
	std::pair<float, std::vector<int>> simulate(Graph *, int);

};


#endif //LAB5_SAAlgorithm_H
