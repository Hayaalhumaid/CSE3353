#ifndef ITERATIVEBFS_H
#define ITERATIVEBFS_H

#include "SearchImpl.h"

class IterativeBFS : public SearchImpl
{
public:
    IterativeBFS();
    ~IterativeBFS();

    int SearchList(const std::vector<std::vector<int>>& graph_list, const std::vector<std::vector<double>> &weights, const std::vector<std::vector<double>> &positions, int source, int destination);
    int SearchMatrix(const std::vector<std::vector<int>>& graph_matrix, const std::vector<std::vector<double>> &weights, const std::vector<std::vector<double>> &positions, int source, int destination);

    std::string GetName();
    std::vector<int> GetParents();
private:

    std::vector<int> parent;
};

#endif // ITERATIVEBFS_H
