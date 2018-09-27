
#include "IterativeDFS.h"

#include <stack>
#include <algorithm>

IterativeDFS::IterativeDFS()
{

}

IterativeDFS::~IterativeDFS()
{

}

int IterativeDFS::SearchList(const std::vector<std::vector<int>>& graph_list, const std::vector<std::vector<double>> &weights, const std::vector<std::vector<double>> &positions, int source, int destination)
{
    parent.assign(graph_list.size(), -1);
    std::vector<int> used(graph_list.size(), 0);
    int explored = 0;

    std::stack<int> order;
    order.push(source);
    while(!order.empty())
    {
        explored++;

        int v = order.top();
        order.pop();

        if (v == destination)
            break;
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
    }

    return explored;
}

int IterativeDFS::SearchMatrix(const std::vector<std::vector<int>>& graph_matrix, const std::vector<std::vector<double>> &weights, const std::vector<std::vector<double>> &positions, int source, int destination)
{
    parent.assign(graph_matrix.size(), -1);
    std::vector<int> used(graph_matrix.size(), 0);
    int explored = 0;

    std::stack<int> order;
    order.push(source);
    while(!order.empty())
    {
        explored++;

        int v = order.top();
        order.pop();

        if (v == destination)
            break;
        used[v] = 1;

        for (size_t i = 0; i < graph_matrix[v].size(); ++i)
        {
            int to = source;
            if (graph_matrix[v][i] == 1)
                to = i;
            if (used[to] == 0)
            {
                parent[to] = v;
                order.push(to);
            }
        }
    }

    return explored;
}

std::string IterativeDFS::GetName()
{
    return "DFS iterative";
}

std::vector<int> IterativeDFS::GetParents()
{
    return parent;
}
