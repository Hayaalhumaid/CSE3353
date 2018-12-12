#ifndef LAB4_GAALGORITHM_H
#define LAB4_GAALGORITHM_H

#include <deque>
#include <vector>
#include "Graph.h"
#include <random>

class GAAlgorithm {
private:
    int population_size = 10;
    std::vector<std::pair<float, std::vector<int>>> population;
    std::vector<std::pair<float, std::vector<int>>> next_gen_population;
    std::pair<float, std::vector<int>> global_be;
    int max_iteration = 10;

    std::random_device rd;  
    std::mt19937 gen{rd()}; 

    int node_size = 0;

    int total_ind;

    int sel_criteria = 0;
    float sel_percent = 0.4f;
    int crossover_criteria = 0;
    float crossover_percent = 0.6f;
    float crossover_sub = 0.3f;
    int mutation_crit = 0;
    float rate_of_mutation = 0.05f;

    void init_generate(Graph *,int);
    void get_best();
    void population_gen(Graph *);
    void selection();
    void crossover(Graph *);
    void mutation();
    float path_cost_get(Graph *,const std::vector<int>&, int);
    bool valid_gen(const std::vector<int>&);
    static bool sort_cost(const std::pair<float, std::vector<int>> &p1, const std::pair<float, std::vector<int>> &p2);

public:
    GAAlgorithm() = default;
    std::pair<float, std::vector<int>> genetic_search(Graph *, int);
};


#endif //LAB4_GAAlgorithm_H
