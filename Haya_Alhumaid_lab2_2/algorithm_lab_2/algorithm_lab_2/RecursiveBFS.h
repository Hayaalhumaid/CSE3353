#ifndef RECURSIVEBFS_H
#define RECURSIVEBFS_H

#include "SearchImpl.h"

#include <queue>

class RecursiveBFS : public SearchImpl
{
public:
    RecursiveBFS();
    ~RecursiveBFS();

    int SearchList(const std::vector<std::vector<int>>& graph_list, const std::vector<std::vector<double>> &weights, const std::vector<std::vector<double>> &positions, int source, int destination);
    int SearchMatrix(const std::vector<std::vector<int>>& graph_matrix, const std::vector<std::vector<double>> &weights, const std::vector<std::vector<double>> &positions, int source, int destination);

    std::string GetName();
    std::vector<int> GetParents();
private:
    void _SearchList(const std::vector<std::vector<int>> &graph_list, int destination);
    void _SearchMatrix(const std::vector<std::vector<int>> &graph_matrix, int destination);

    std::vector<int> used;
    std::vector<int> parent;
    int nodes_explored;
    bool destination_hit;

    std::queue<int> order;
};

#endif // RECURSIVEBFS_H
