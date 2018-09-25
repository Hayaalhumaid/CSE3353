#include "stdafx.h"

#include "RecursiveDFS.h"

#include <algorithm>

RecursiveDFS::RecursiveDFS()
{

}

RecursiveDFS::~RecursiveDFS()
{

}

int RecursiveDFS::SearchList(const std::vector<std::vector<int>>& graph_list, const std::vector<std::vector<double>> &weights, const std::vector<std::vector<double>> &positions, int source, int destination)
{
    parent.assign(graph_list.size(), -1);
    used.assign(graph_list.size(), 0);
    nodes_explored = 0;
    destination_hit = false;

    _SearchList(graph_list, source, destination);

    return nodes_explored;
}

int RecursiveDFS::SearchMatrix(const std::vector<std::vector<int>>& graph_matrix, const std::vector<std::vector<double>> &weights, const std::vector<std::vector<double>> &positions, int source, int destination)
{
    parent.assign(graph_matrix.size(), -1);
    used.assign(graph_matrix.size(), 0);
    nodes_explored = 0;
    destination_hit = false;

    _SearchMatrix(graph_matrix, source, destination);

    return nodes_explored;
}


std::string RecursiveDFS::RecursiveDFS::GetName()
{
    return "DFS recursive";
}

std::vector<int> RecursiveDFS::GetParents()
{
    return parent;
}

void RecursiveDFS::_SearchList(const std::vector<std::vector<int>> &graph_list, int current, int destination)
{
    used[current] = 1;
    if (!destination_hit)
        nodes_explored++;
    if (current == destination)
        destination_hit = true;
    if (destination_hit)
        return;

    for (size_t i = 0; i < graph_list[current].size(); ++i)
    {
        int to = graph_list[current][i];
        if (used[to] == 0)
        {
            parent[to] = current;
            _SearchList(graph_list, to, destination);
        }
    }
}

void RecursiveDFS::_SearchMatrix(const std::vector<std::vector<int>> &graph_matrix, int current, int destination)
{
    used[current] = 1;
    if (!destination_hit)
        nodes_explored++;
    if (current == destination)
        destination_hit = true;
    if (destination_hit)
        return;

    for (size_t i = 0; i < graph_matrix[current].size(); ++i)
    {
        int to = current;
        if (graph_matrix[current][i] == 1)
            to = i;

        if (used[to] == 0)
        {
            parent[to] = current;
            _SearchMatrix(graph_matrix, to, destination);
        }
    }
}
