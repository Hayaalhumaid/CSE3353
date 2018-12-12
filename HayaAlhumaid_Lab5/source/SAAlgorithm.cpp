#include "SAAlgorithm.h"
#include <random>
#include <iostream>
#include <algorithm>
#include <limits>
#include <cmath>

std::pair<float, std::vector<int>> SAAlgorithm::simulate(Graph *g, int source)
{
	std::uniform_int_distribution<> randomNode(1, g->map.size()-1);
	std::uniform_real_distribution<> randomFloat(0, 1);

	best_tour.second.clear();
	for (size_t i = 0; i < g->map.size(); ++i)
		if (i+1 != source)
			best_tour.second.push_back(i + 1);
	best_tour.first = path_cost_get(g, best_tour.second, source);

	for (int s = 0; s < 10; ++s)
	{
		std::random_shuffle(best_tour.second.begin(), best_tour.second.end());
		temperature = std::numeric_limits<float>::max();
		while (temperature > 1)
		{
			for (size_t i = 0; i < best_tour.second.size(); ++i)
			{
				std::pair<float, std::vector<int>> new_tour(best_tour);
				//int id = randomNode(gen);
				//std::swap(new_tour.second[id - 1], new_tour.second[id % best_tour.second.size()]);
				//std::swap(new_tour.second[i], new_tour.second[(i+1) % best_tour.second.size()]);
				std::swap(new_tour.second[randomNode(gen) - 1], new_tour.second[randomNode(gen) - 1]);
				new_tour.first = path_cost_get(g, new_tour.second, source);
				if (p_function(best_tour.first, new_tour.first, temperature) > randomFloat(gen))
				{
					best_tour = new_tour;
					break;
				}
			}

			temperature *= 0.9f;
		}
	}

	return best_tour;
}

float SAAlgorithm::p_function(float e1, float e2, float temp)
{
	float diff = e2 - e1;
	if (diff < 0)
		return 1;
	else
		return static_cast<float>(std::exp(-diff / temp));
}

float SAAlgorithm::path_cost_get(Graph * g, const std::vector<int> &vec, int src) {
	int temporary_src = src;
	float temporary_cost = 0;

	for (size_t j = 0; j<vec.size(); ++j) {
		temporary_cost += g->map_for_cache[temporary_src - 1][vec[j] - 1];
		temporary_src = vec[j];
	}
	temporary_cost += g->map_for_cache[temporary_src - 1][src - 1];

	return temporary_cost;
}