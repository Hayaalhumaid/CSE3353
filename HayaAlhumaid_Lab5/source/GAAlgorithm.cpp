#include "GAAlgorithm.h"
#include <random>
#include <iostream>
#include <algorithm>
#include <limits>

std::pair<float, std::vector<int>> GAAlgorithm::genetic_search(Graph * g, int source) {
    int num_iteration = 0;
    global_be.second.clear();
    global_be.first = std::numeric_limits<float>::max();
    

    node_size = g->map.size();

    
    init_generate(g,source);

    while(num_iteration <= max_iteration){
        get_best();
        population_gen(g);

        num_iteration++;
    }

    return global_be;
}

void GAAlgorithm::get_best() {
    for (size_t i=0; i<population.size(); ++i) {
        if(population[i].first < global_be.first)
            global_be = population[i];
    }
    global_be = population[0];
}

void GAAlgorithm::population_gen(Graph* g) {
    total_ind = 0;
    selection();

    crossover(g);

    population = next_gen_population;

    mutation();

    next_gen_population.clear();
}

void GAAlgorithm::selection() {
    float selectNum = sel_percent * population_size;

    if(sel_criteria == 0){
        for (int i=0; i<selectNum; ++i) {
            next_gen_population.push_back(population[i]);
            total_ind++;
        }
    }
    else if(sel_criteria == 1){
        for (int i=0; i<selectNum; i=i+2) {
            next_gen_population.push_back(population[i]);
            total_ind++;
        }
    }
    else{

    }

}

void GAAlgorithm::crossover(Graph * g) {
    float crossover_num = crossover_percent * population_size;

    float subsetSize = population[0].second.size() * crossover_sub;

    std::uniform_int_distribution<> disC((int)(subsetSize), (int)(node_size-subsetSize-1));


    if(crossover_criteria == 0){
        for (int i=total_ind; i<(int)(crossover_num + total_ind);) {
            std::vector<int> temp_ = population[i].second;
            i++;


            std::vector<int> temp_new = population[i].second;
            i++;

                int index = disC(gen);

                std::vector<int> subset_1;
                std::vector<int> subset_2;
                std::vector<int> temp_new_1;
                std::vector<int> temp_new_2;

                temp_new_1.resize(temp_.size());
                temp_new_2.resize(temp_new.size());
                for (int k = 0; k < (int)(subsetSize); ++k) {
                    subset_1.push_back(temp_[k + index]);
                    subset_2.push_back(temp_new[k + index]);
                }

                for (int i=0, k=0; i<temp_.size(); ++i) {
                    if(i >= index && i < (int)(index+subsetSize)){
                        temp_new_1[i] = temp_[i];
                    }
                    else if(find(subset_1.begin(), subset_1.end(), temp_new[k]) == subset_1.end()){
                        temp_new_1[i] = temp_new[k];
                        k++;
                    }
                    else{
                        while(find(subset_1.begin(), subset_1.end(), temp_new[k]) != subset_1.end()){
                            k++;
                        }
                        temp_new_1[i] = temp_new[k];
                        k++;
                    }

                }

                for (int i=0, k=0; i< temp_new.size(); ++i) {
                    if(i >= index && i < (int)(index+subsetSize)){
                        temp_new_2[i] = temp_new[i];
                    }
                    else if(find(subset_2.begin(), subset_2.end(), temp_[k]) == subset_2.end()){
                        temp_new_2[i] = temp_[k];
                        k++;
                    }
                    else{
                        while(find(subset_2.begin(), subset_2.end(), temp_[k]) != subset_2.end()){
                            k++;
                        }
                        temp_new_2[i] = temp_[k];
                        k++;
                    }

                }

                    float current_cost_ = path_cost_get(g, temp_new_1, 1);
                    float current_cost_new = path_cost_get(g, temp_new_2, 1);

                    next_gen_population.push_back(std::make_pair(current_cost_, temp_new_1));
                    next_gen_population.push_back(std::make_pair(current_cost_new, temp_new_2));

        }
        total_ind = 0;
    }
    else if(crossover_criteria == 1){
    }
    else{

    }

}

void GAAlgorithm::mutation() {

    std::uniform_real_distribution<> disc_mut2{0, 1};

    std::uniform_int_distribution<> disc_mut1{0, (int)(population[0].second.size()-1)};

    for (int i = 0; i < population_size; ++i) {
        auto mutation_do = (float) (disc_mut2(gen));
        if (mutation_do < rate_of_mutation) {
            if (mutation_crit == 0) {

                int ind_1 = disc_mut1(gen);
                int ind_2 = disc_mut1(gen);

                int temp_ = population[i].second[ind_1];
                int temp_new = population[i].second[ind_2];
                population[i].second[ind_1] = temp_new;
                population[i].second[ind_2] = temp_;
            }
            else if (mutation_crit == 1) {

            }
            else {

            }
        }
    }

}

void GAAlgorithm::init_generate(Graph* g, int src) {
    float current_cost = 0;
    std::vector<int> original_pop;
    for (size_t i = 0; i < g->map.size(); i++){
        if (i + 1 != src)
            original_pop.push_back(i + 1);
    }
    current_cost = path_cost_get(g, original_pop, src);
    population.push_back(std::make_pair(current_cost, original_pop));

    auto rng = std::default_random_engine {};
    for(int i=1; i<population_size; i++){
        std::shuffle(std::begin(original_pop), std::end(original_pop), rng);

        while(!valid_gen(original_pop)){
            original_pop.clear();
            for (size_t i = 0; i < g->map.size(); i++){
                if (i + 1 != src)
                    original_pop.push_back(i + 1);
            }
            std::shuffle(std::begin(original_pop), std::end(original_pop), rng);
        }
        current_cost = path_cost_get(g, original_pop, src);
        population.push_back(std::make_pair(current_cost, original_pop));
    }

    std::sort(population.begin(), population.end(), sort_cost);

}

float GAAlgorithm::path_cost_get(Graph * g, const std::vector<int> &vec, int src) {
    int temporary_src = src;
    float temporary_cost = 0;

    for (size_t j=0; j<vec.size(); ++j) {
        temporary_cost += g->map_for_cache[temporary_src-1][vec[j]-1];
        temporary_src = vec[j];
    }
    temporary_cost += g->map_for_cache[temporary_src-1][src-1];

    return temporary_cost;
}

bool GAAlgorithm::valid_gen(const std::vector<int> &vec) {
    if(vec.size() == node_size){
        return false;
    }

        for(size_t k=0; k<vec.size(); k++){
            if(vec[k] > node_size || vec[k] == 0){
                return false;
            }
        }
    return true;
}


bool GAAlgorithm::sort_cost(const std::pair<float, std::vector<int>> &p1, const std::pair<float, std::vector<int>> &p2){
    return (p1.first < p2.first);
}