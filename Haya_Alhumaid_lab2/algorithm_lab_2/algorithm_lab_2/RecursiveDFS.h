#ifndef RECURSIVEDFS_H
#define RECURSIVEDFS_H

#include "SearchImpl.h"

class RecursiveDFS : public SearchImpl
{
public:
    RecursiveDFS();
    ~RecursiveDFS();

    int SearchList(const std::vector<std::vector<int>>& graph_list, const std::vector<std::vector<double>> &weights, const std::vector<std::vector<double>> &positions, int source, int destination);
    int SearchMatrix(const std::vector<std::vector<int>>& graph_matrix, const std::vector<std::vector<double>> &weights, const std::vector<std::vector<double>> &positions, int source, int destination);

    std::string GetName();
    std::vector<int> GetParents();
private:
    void _SearchList(const std::vector<std::vector<int>> &graph_list, int current, int destination);
    void _SearchMatrix(const std::vector<std::vector<int>> &graph_matrix, int current, int destination);

    std::vector<int> used;
    std::vector<int> parent;
    int nodes_explored;
    bool destination_hit;
};

#endif // RECURSIVEDFS_H
