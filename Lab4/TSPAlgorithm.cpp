
#include <algorithm>
#include <iostream>
#include <math.h>
#include <cmath>

#include "TSPAlgorithm.h"

float TSPAlgorithm::find_cost(Graph* g, int d1, int d2){
    float x, y, z;

    x = powf(abs(g->map[d1][0] - g->map[d2][0]), 2);
    y = powf(abs(g->map[d1][1] - g->map[d2][1]), 2);
    z = powf(abs(g->map[d1][2] - g->map[d2][2]), 2);

    return sqrtf(x + y + z);

}

std::pair<float,std::vector<int>> TSPAlgorithm::TSP_Naive(Graph *g, int src) {
    std::pair<float,std::vector<int>> path_final;
    path_final.first = MAXFLOAT;

    int num_iteration = 0;

    std::vector<int> permute_vert;
    for(int i=0; i < g->map.size(); i++){
        if(i+1!=src)
            permute_vert.push_back(i+1);
    }

    do{
        float temporary_cost_min = 0;
        int temporary_src = src;

        for (int i=0; i < permute_vert.size(); ++i) {
            temporary_cost_min += find_cost(g, temporary_src, permute_vert[i]);
            temporary_src = permute_vert[i];
        }
        temporary_cost_min += find_cost(g, temporary_src, src);

        if(temporary_cost_min < path_final.first){
            path_final.second = permute_vert;
            path_final.second.insert(path_final.second.begin(), src);
            path_final.first = temporary_cost_min;
        }

        num_iteration++;

    }
    while(std::next_permutation(permute_vert.begin(), permute_vert.end()));

    return path_final;
}


std::pair<float,std::vector<int>> TSPAlgorithm::TSPDynamic(Graph *g, int src) {
    int num_iteration = 0;

    std::vector<int> permute_vert;
    for(int i=0; i < g->map.size(); i++){
        if(i+1!=src)
            permute_vert.push_back(i+1);
    }

    std::pair<float,std::vector<int>> path_final;
    path_final = TSPDynUtil(g, src, src, permute_vert,num_iteration);

    return path_final;
}

std::pair<float,std::vector<int>> TSPAlgorithm::TSPDynUtil(Graph* g, int src, int tempSrc, std::vector<int> vec, int& num_iteration){

    std::vector<int> temppath_final;
    float minCost = MAXFLOAT;

    if(vec.empty()){
        std::cerr << "Error, cannot start with permutations vector empty";
    }

    else if(vec.size() <= 2){
        float a = g->map_for_cache[tempSrc-1][vec[0]-1] + g->map_for_cache[vec[0]-1][vec[1]-1] + g->map_for_cache[vec[1]-1][src-1];
        float b = g->map_for_cache[tempSrc-1][vec[1]-1] + g->map_for_cache[vec[1]-1][vec[0]-1] + g->map_for_cache[vec[0]-1][src-1];


        if(a<b){
            temppath_final = {src, vec[1],vec[0]};
            return std::make_pair(a, temppath_final);
        }
        else {
            temppath_final = {src, vec[0],vec[1]};
            return std::make_pair(b, temppath_final);
        }
    }

    else{
        std::pair<float,std::vector<int>> fin_pair_;

        for (int i=0; i<vec.size(); ++i) {
            std::vector<int> temporary_vector = vec;
            temporary_vector.erase(temporary_vector.begin()+i);
            std::pair<float,std::vector<int>> cost_pair_ = TSPAlgorithm::TSPDynUtil(g, src, vec[i], temporary_vector, num_iteration);

            cost_pair_.first += g->map_for_cache[tempSrc-1][vec[i]-1];
            cost_pair_.second.push_back(vec[i]);

            if( (cost_pair_.first<minCost)  ){
                fin_pair_ = cost_pair_;
                minCost = cost_pair_.first;
            }

            num_iteration++;
        }
        return fin_pair_;
    }
}