#ifndef LAB5_PSOALGORITHM_H
#define LAB5_PSOALGORITHM_H

#include <deque>
#include <vector>
#include "Graph.h"
#include <random>

class PSOAlgorithm {
private:

	struct Particle
	{
		std::pair<float, std::vector<int>> solution; // position
		std::pair<float, std::vector<int>> p_best;

		std::vector<std::pair<int, int>> velocity; // swap sequence
	};

	std::random_device rd;
	std::mt19937 gen{ rd() };

	float path_cost_get(Graph *, const std::vector<int> &, int);
	std::vector<std::pair<int, int>> get_swap_sequense(const std::vector<int>&, std::vector<int>);

public:
    PSOAlgorithm() = default;
	std::pair<float, std::vector<int>> simulate(Graph *, int);

};


#endif //LAB5_PSOAlgorithm_H
