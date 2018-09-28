#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "SearchImpl.h"

class Dijkstra : public SearchImpl
{
public:
    Dijkstra();
    ~Dijkstra();

    int SearchList(const std::vector<std::vector<int>>& graph_list, const std::vector<std::vector<double>> &weights, const std::vector<std::vector<double>> &positions, int source, int destination);
    int SearchMatrix(const std::vector<std::vector<int>>& graph_matrix, const std::vector<std::vector<double>> &weights, const std::vector<std::vector<double>> &positions, int source, int destination);

    std::string GetName();
    std::vector<int> GetParents();
private:

    std::vector<int> parent;
};

#endif // DIJKSTRA_H
