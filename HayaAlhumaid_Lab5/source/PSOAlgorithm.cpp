#include "PSOAlgorithm.h"
#include <random>
#include <iostream>
#include <algorithm>
#include <limits>
#include <cmath>

std::pair<float, std::vector<int>> PSOAlgorithm::simulate(Graph *g, int source)
{
	std::uniform_real_distribution<> randomFloat(0, 1);
	// learning factors for p_best and g_best
	// probability that all pairs from a swap sequence are included
	const float alpha = 0.5f, beta = 0.9f; 
	// max speed
	const size_t max_velocity_size = 50;

	const int num_of_particles = 100;
	const int num_of_iterations = 10;

	std::pair<float, std::vector<int>> g_best;
	g_best.first = std::numeric_limits<float>::max();

	std::vector<Particle> particles;
	for (int i = 0; i < num_of_particles; ++i)
	{
		Particle particle;
		// init
		for (size_t j = 1; j < g->map.size(); ++j)
			particle.solution.second.push_back(j + 1);
		std::random_shuffle(particle.solution.second.begin(), particle.solution.second.end());
		particle.solution.first = path_cost_get(g, particle.solution.second, source);
		particle.p_best = particle.solution;

		particles.push_back(particle);
	}

	for (int t = 0; t < num_of_iterations; ++t)
	{
		for (size_t i = 0; i < particles.size(); ++i)
		{
			if (particles[i].p_best.first < g_best.first)
				g_best = particles[i].p_best;
		}

		for (size_t i = 0; i < particles.size(); ++i)
		{
			std::vector<std::pair<int, int>> p_best_swap_seq = get_swap_sequense(particles[i].solution.second, particles[i].p_best.second);
			std::vector<std::pair<int, int>> g_best_swap_seq = get_swap_sequense(particles[i].solution.second, g_best.second);

			float alpha_per_swap = static_cast<float>(std::pow(alpha, 1.0 / p_best_swap_seq.size()));
			float beta_per_swap = static_cast<float>(std::pow(beta, 1.0 / g_best_swap_seq.size()));


			// update velocity
			// v(t)=v(t-1)+α*(pbest-x(t-1)+β(gbest-x(t-1))
			for (size_t j = 0; j < p_best_swap_seq.size(); ++j)
			{
				float random = static_cast<float>(randomFloat(gen));
				if (alpha_per_swap > random)
					particles[i].velocity.push_back(p_best_swap_seq[j]);
			}
			for (size_t j = 0; j < g_best_swap_seq.size(); ++j)
			{
				float random = static_cast<float>(randomFloat(gen));
				if (beta_per_swap > random)
					particles[i].velocity.push_back(g_best_swap_seq[j]);
			}

			// check for max_velocity
			if (particles[i].velocity.size() > max_velocity_size)
			{
				particles[i].velocity = std::vector<std::pair<int, int>>(particles[i].velocity.end() - particles[i].velocity.size() + max_velocity_size/2, particles[i].velocity.end());
			}

			// update position
			for (size_t j = 0; j < particles[i].velocity.size(); ++j)
			{
				int temp = particles[i].solution.second[particles[i].velocity[j].first];
				particles[i].solution.second[particles[i].velocity[j].first] = particles[i].solution.second[particles[i].velocity[j].second];
				particles[i].solution.second[particles[i].velocity[j].second] = temp;
			}
			particles[i].solution.first = path_cost_get(g, particles[i].solution.second, source);
			if (particles[i].solution.first < particles[i].p_best.first)
				particles[i].p_best = particles[i].solution;
		}
	}

	return g_best;
}


float PSOAlgorithm::path_cost_get(Graph * g, const std::vector<int> &vec, int src) {
	int temporary_src = src;
	float temporary_cost = 0;

	for (size_t j = 0; j<vec.size(); ++j) {
		temporary_cost += g->map_for_cache[temporary_src - 1][vec[j] - 1];
		temporary_src = vec[j];
	}
	temporary_cost += g->map_for_cache[temporary_src - 1][src - 1];

	return temporary_cost;
}

std::vector<std::pair<int, int>> PSOAlgorithm::get_swap_sequense(const std::vector<int> &sol1, std::vector<int> sol2)
{
	std::vector<std::pair<int, int>> swap_sequence;
	for (size_t i = 0; i < sol1.size(); ++i)
	{
		if (sol1[i] != sol2[i])
		{
			swap_sequence.push_back(std::make_pair(i, (std::find(sol2.begin(), sol2.end(), sol1[i]) - sol2.begin())));

			int temp = sol2[swap_sequence.back().first];
			sol2[swap_sequence.back().first] = sol2[swap_sequence.back().second];
			sol2[swap_sequence.back().second] = temp;
		}
	}
	return swap_sequence;
}
