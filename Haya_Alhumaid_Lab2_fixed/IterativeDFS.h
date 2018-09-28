#ifndef ITERATIVEDFS_H
#define ITERATIVEDFS_H

#include "SearchImpl.h"

class IterativeDFS : public SearchImpl
{
public:
    IterativeDFS();
    ~IterativeDFS();

    int SearchList(const std::vector<std::vector<int>>& graph_list, const std::vector<std::vector<double>> &weights, const std::vector<std::vector<double>> &positions, int source, int destination);
    int SearchMatrix(const std::vector<std::vector<int>>& graph_matrix, const std::vector<std::vector<double>> &weights, const std::vector<std::vector<double>> &positions, int source, int destination);

    std::string GetName();
    std::vector<int> GetParents();
private:

    std::vector<int> parent;
};

#endif // ITERATIVEDFS_H
