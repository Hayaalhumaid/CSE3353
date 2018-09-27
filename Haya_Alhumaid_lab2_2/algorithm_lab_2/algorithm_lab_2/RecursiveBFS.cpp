
#include "RecursiveBFS.h"

#include <algorithm>

RecursiveBFS::RecursiveBFS()
{

}

RecursiveBFS::~RecursiveBFS()
{

}

int RecursiveBFS::SearchList(const std::vector<std::vector<int>>& graph_list, const std::vector<std::vector<double>> &weights, const std::vector<std::vector<double>> &positions, int source, int destination)
{
    order = std::queue<int>();
    parent.assign(graph_list.size(), -1);
    used.assign(graph_list.size(), 0);
    nodes_explored = 0;
    destination_hit = false;

    order.push(source);
    _SearchList(graph_list, destination);

    return nodes_explored;
}

int RecursiveBFS::SearchMatrix(const std::vector<std::vector<int>>& graph_matrix, const std::vector<std::vector<double>> &weights, const std::vector<std::vector<double>> &positions, int source, int destination)
{
    order = std::queue<int>();
    parent.assign(graph_matrix.size(), -1);
    used.assign(graph_matrix.size(), 0);
    nodes_explored = 0;
    destination_hit = false;

    order.push(source);
    _SearchMatrix(graph_matrix, destination);

    return nodes_explored;
}

std::string RecursiveBFS::GetName()
{
    return "BFS recursive";
}

std::vector<int> RecursiveBFS::GetParents()
{
    return parent;
}

void RecursiveBFS::_SearchList(const std::vector<std::vector<int>> &graph_list, int destination)
{
    if (order.empty())
        return;

    int v = order.front();
    order.pop();

    if (!destination_hit)
        nodes_explored++;
    if (v == destination)
        destination_hit = true;
    if (destination_hit)
        return;

    used[v] = 1;
    for (size_t i = 0; i < graph_list[v].size(); ++i)
    {
        int to = graph_list[v][i];
        if (used[to] == 0)
        {
            parent[to] = v;
            order.push(to);
        }
    }
    _SearchList(graph_list, destination);
}

void RecursiveBFS::_SearchMatrix(const std::vector<std::vector<int>> &graph_matrix, int destination)
{
    if (order.empty())
        return;

    int v = order.front();
    order.pop();

    if (!destination_hit)
        nodes_explored++;
    if (v == destination)
        destination_hit = true;
    if (destination_hit)
        return;
    used[v] = 1;

    for (size_t i = 0; i < graph_matrix[v].size(); ++i)
    {
        int to = v;
        if (graph_matrix[v][i] == 1)
            to = i;
        if (used[to] == 0)
        {
            parent[to] = v;
            order.push(to);
        }
    }
    _SearchMatrix(graph_matrix, destination);
}
