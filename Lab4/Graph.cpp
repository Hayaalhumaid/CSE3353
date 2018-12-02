#include "Graph.h"
#include <math.h>

std::vector<std::vector<float>> Graph::cost_calculation(){
    int array_size = map.size();
    map_for_cache.resize(map.size());
    float x, y, z;

    for(int i=0; i<array_size; i++){
        for (int j=0; j <array_size; ++j) {
            if(i != j){
                x = powf(abs(map[i+1][0] - map[j+1][0]), 2);
                y = powf(abs(map[i+1][1] - map[j+1][1]), 2);
                z = powf(abs(map[i+1][2] - map[j+1][2]), 2);
                map_for_cache[i].push_back(sqrtf(x + y + z));

            } else{
                map_for_cache[i].push_back(0);
            }
        }
    }

    return map_for_cache;
}