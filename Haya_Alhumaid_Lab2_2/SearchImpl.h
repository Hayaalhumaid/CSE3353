#ifndef SEARCHIMPL_H
#define SEARCHIMPL_H

#include <vector>
#include <string>

// Abstract class for all searching algorithms
// Is used in Srategy pattern
class SearchImpl
{
public:
    virtual ~SearchImpl() {}

    // Search functions return the number of nodes explored
    virtual int SearchList(const std::vector<std::vector<int>>& graph_list, const std::vector<std::vector<double>> &weights, const std::vector<std::vector<double>> &positions, int source, int destination) = 0;
    virtual int SearchMatrix(const std::vector<std::vector<int>>& graph_matrix, const std::vector<std::vector<double>> &weights, const std::vector<std::vector<double>> &positions, int source, int destination) = 0;

    virtual std::string GetName() = 0;
    // Returns the list which contains a parent for each vertex, from which the path can be restored
    virtual std::vector<int> GetParents() = 0;
};

#endif // SEARCHIMPL_H
