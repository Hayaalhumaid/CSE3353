#ifndef LAB4_TABUALGORITHM_H
#define LAB4_TABUALGORITHM_H

#include <vector>
#include <deque>
#include <list>
#include "Graph.h"


class TabuAlgorithm{
private:
    std::vector<std::deque<int>> nbd;
    std::pair<float, std::deque<int>> current;
    std::pair<float, std::deque<int>> global;

    int max_iteration = 300;
    std::list<std::deque<int>> tabu_algo_list;
    int tabu_algo_listSize = 5;
    size_t nbd_size = 8; 
    int nbd_criteria = 1;

    std::deque<int> sol = {1,6,4,3,2,5,7};
    std::deque<int> sol2 = {7,5,2,3,4,6,1};
    int num_iteration = 0;

public:
    TabuAlgorithm() = default;
    std::pair<float, std::deque<int>> tabu_search(Graph *, int);
    void gen_nbd();
    std::pair<float, std::deque<int>> get_best(Graph *, int);
    
};


#endif //LAB4_TABUALGORITHM_H
