#include "Dijkstra.h"

#include <limits>

Dijkstra::Dijkstra()
{

}

Dijkstra::~Dijkstra()
{

}

int Dijkstra::SearchList(const std::vector<std::vector<int>>& graph_list, const std::vector<std::vector<double>> &weights, const std::vector<std::vector<double>> &positions, int source, int destination)
{
    parent.assign(graph_list.size(), -1);

    std::vector<int> used(graph_list.size(), 0);
    std::vector<double> cost(graph_list.size(), std::numeric_limits<double>::max());
    int explored = 0;

    cost[source] = 0;
    for (size_t i = 0; i < graph_list.size(); ++i)
    {
        int v = -1;
        for (size_t j = 0; j < graph_list.size(); ++j)
        {
            if (used[j] == 0 && (v == -1 || cost[j] < cost[v]))
                v = j;
        }
        if (cost[v] == std::numeric_limits<double>::max())
            break;
        used[v] = 1;
        explored++;

        for (size_t j = 0; j < graph_list[v].size(); ++j)
        {
            int to = graph_list[v][j];
            double weight = weights[v][j];
            if (cost[v] + weight < cost[to])
            {
                cost[to] = cost[v] + weight;
                parent[to] = v;
            }
        }
    }

    return explored;
}

int Dijkstra::SearchMatrix(const std::vector<std::vector<int>>& graph_matrix, const std::vector<std::vector<double>> &weights, const std::vector<std::vector<double>> &positions, int source, int destination)
{
    parent.assign(graph_matrix.size(), -1);

    std::vector<int> used(graph_matrix.size(), 0);
    std::vector<double> cost(graph_matrix.size(), std::numeric_limits<double>::max());
    int explored = 0;

    cost[source] = 0;
    for (size_t i = 0; i < graph_matrix.size(); ++i)
    {
        int v = -1;
        for (size_t j = 0; j < graph_matrix.size(); ++j)
        {
            if (used[j] == 0 && (v == -1 || cost[j] < cost[v]))
                v = j;
        }
        if (cost[v] == std::numeric_limits<double>::max())
            break;
        used[v] = 1;
        explored++;

        for (size_t j = 0; j < graph_matrix[v].size(); ++j)
        {
            int to = v;
            if (graph_matrix[v][j] == 1)
                to = j;
            else
                continue;
            double weight = weights[v][to];

            if (cost[v] + weight < cost[to])
            {
                cost[to] = cost[v] + weight;
                parent[to] = v;
            }
        }
    }

    return explored;
}

std::string Dijkstra::GetName()
{
    return "Dijkstra";
}

std::vector<int> Dijkstra::GetParents()
{
    return parent;
}
