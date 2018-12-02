
#include "TabuAlgorithm.h"
#include <cmath>
#include <iostream>
#include <algorithm>
#include <random>


std::pair<float, std::deque<int>> TabuAlgorithm::tabu_search(Graph * g, int src) {


    current.first = MAXFLOAT;
    current.second.clear();
    global.first = MAXFLOAT;
    global.second.clear();
    std::vector<int> temporary_vector;
    for(int i=1; i<g->map.size();i++){
        temporary_vector.push_back(i+1);
    }

    auto rng = std::default_random_engine {};
    std::shuffle(std::begin(temporary_vector), std::end(temporary_vector), rng);

    for(int i=0; i<temporary_vector.size();i++){
        current.second.push_back(temporary_vector[i]);
    }


    while(num_iteration < max_iteration){
        gen_nbd();
        current = get_best(g, src);
        bool input_tabu_algo = false;
        for (std::list<std::deque<int>>::const_iterator iterator = tabu_algo_list.begin(), end = tabu_algo_list.end(); iterator != end; ++iterator) {
            if(*iterator == current.second)
                input_tabu_algo = true;
        }

        if(!input_tabu_algo){
            
            if(tabu_algo_list.size() == tabu_algo_listSize){
                tabu_algo_list.pop_front();
                tabu_algo_list.push_back(current.second);
            }
            else{
                tabu_algo_list.push_back(current.second);
            }
            if(current.first < global.first) {
                global = current;
                global.second.push_front(1);
            }
        }
        num_iteration++;
    }
    std::cout << num_iteration << std::endl;
    return global;
}

void TabuAlgorithm::gen_nbd() {
    int nbd_ind = 0;
    nbd.clear();

    if(nbd_criteria == 0){
        std::vector<int> use_random;
        bool duplicate_check = false;
        std::deque<int> temporary_nbd = current.second;

        int previous_n = 0;


        std::random_device rd;  
        std::mt19937 gen(rd()); 
        std::uniform_int_distribution<> dis(0, temporary_nbd.size()-1);
        std::uniform_int_distribution<> dis2(0, 1);

        while (nbd_ind < nbd_size){
            duplicate_check = false;
            int ind_swap = dis(gen);

            if(ind_swap == 0){
                previous_n = 1;
            }
            else if(ind_swap == temporary_nbd.size()-1){
                previous_n = -1;
            }
            else{
                previous_n = dis2(gen);
                if(previous_n == 0)
                    previous_n = -1;
            }


            for (int i=0; i<use_random.size(); ++i) {
                if(use_random[i] == ind_swap){
                    duplicate_check = true;
                }
            }
            if(!duplicate_check) {
                use_random.push_back(ind_swap);
                int temporary_ind_1 = temporary_nbd[ind_swap];
                int temporary_ind_2 = temporary_nbd[ind_swap + previous_n];
                temporary_nbd[ind_swap + previous_n] = temporary_ind_1;
                temporary_nbd[ind_swap] = temporary_ind_2;
                nbd.push_back(temporary_nbd);
                temporary_nbd[ind_swap + previous_n] = temporary_ind_2;
                temporary_nbd[ind_swap] = temporary_ind_1;
            }
            nbd_ind++;
        }
    }

    else if(nbd_criteria == 1){
        std::deque<int> temporary_nbd = current.second;
        nbd.clear();
        int ind_1 = 0;

        std::random_device rd;  
        std::mt19937 gen(rd()); 
        std::uniform_int_distribution<> dis(0, temporary_nbd.size()-1);

        while (nbd_ind < nbd_size){
            int random_ind = dis(gen);
            while(random_ind == ind_1){
                random_ind = dis(gen);
            }
            int temporary_ind_1 = temporary_nbd[ind_1];
            int temporary_ind_2 = temporary_nbd[random_ind];


            temporary_nbd[ind_1] = temporary_ind_2;
            temporary_nbd[random_ind] = temporary_ind_1;


            nbd.push_back(temporary_nbd);

            temporary_nbd[ind_1] = temporary_ind_1;
            temporary_nbd[random_ind] = temporary_ind_2;

            ind_1++;

            nbd_ind++;
        }
    }

    else if(nbd_criteria == 2){
        std::deque<int> temporary_nbd = current.second;
        nbd.clear();
        int ind_1 = 0;
        int ind_2 = 2;

        while (nbd_ind < nbd_size){
            int temporary_ind_1 = temporary_nbd[ind_1];
            int temporary_ind_2 = temporary_nbd[ind_2];
            temporary_nbd[ind_1] = temporary_ind_2;
            temporary_nbd[ind_2] = temporary_ind_1;
            nbd.push_back(temporary_nbd);

            temporary_nbd[ind_1] = temporary_ind_1;
            temporary_nbd[ind_2] = temporary_ind_2;

            ind_1++;
            ind_2++;
            nbd_ind++;
        }
    }

    else{
        std::cerr << "Wrong  Criteria For nbd." << std::endl;
    }

}

std::pair<float, std::deque<int>> TabuAlgorithm::get_best(Graph* g, int src) {
    float cost_best = MAXFLOAT;
    float temporary_cost_min = 0;
    float a, b, c, d;
    std::deque<int> path_best;
    src = 1;
    int temporary_src = src;
    for (int i=0; i<nbd.size(); ++i){

        for (int j=0; j<nbd[i].size(); ++j) {
            temporary_cost_min += g->map_for_cache[temporary_src-1][nbd[i][j]-1];
            temporary_src = nbd[i][j];
        }
        temporary_cost_min += g->map_for_cache[temporary_src-1][src-1];


        if(temporary_cost_min < cost_best){
            cost_best = temporary_cost_min;
            path_best = nbd[i];
        }
        temporary_cost_min = 0;
        temporary_src = src;
    }
    return std::make_pair(cost_best, path_best);
}