#include "stdafx.h"

#include "AStar.h"

#include <limits>
#include <math.h>

AStar::AStar()
{

}

AStar::~AStar()
{

}

int AStar::SearchList(const std::vector<std::vector<int>>& graph_list, const std::vector<std::vector<double>> &weights, const std::vector<std::vector<double>> &positions, int source, int destination)
{
    parent.assign(graph_list.size(), -1);

    // 0 -- untouched; 1 -- to be reviewed; 2 -- visited;
    std::vector<int> used(graph_list.size(), 0);
    std::vector<double> gScore(graph_list.size(), std::numeric_limits<double>::max());
    std::vector<double> fScore(graph_list.size(), std::numeric_limits<double>::max());
    int explored = 0;

    used[source] = 1;
    gScore[source] = 0;
    fScore[source] = std::numeric_limits<double>::max()-1;

    while(1)
    {
        int v = -1;
        for (size_t i = 0; i < graph_list.size(); ++i)
        {
            if (used[i] == 1)
            {
                if (v == -1 || fScore[i] < fScore[v])
                    v = i;
            }
        }
        if (v == -1)
            break;
        if (v == destination)
            break;

        used[v] = 2;

        explored++;

        for (size_t i = 0; i < graph_list[v].size(); ++i)
        {
            int to = graph_list[v][i];
            double cost = weights[v][i];
            if (used[to] == 2)
                continue;

            double tentative_gScore = gScore[v] + cost;

            if (used[to] != 1)
                used[to] = 1;
            else if (tentative_gScore >= gScore[to])
                continue;

            parent[to] = v;
            gScore[to] = tentative_gScore;
            double distance = sqrt((positions[v][0]-positions[to][0]) * (positions[v][0]-positions[to][0])
                    + (positions[v][1]-positions[to][1]) * (positions[v][1]-positions[to][1])
                    + (positions[v][2]-positions[to][2]) * (positions[v][2]-positions[to][2]));
            fScore[to] = gScore[to] + distance*(1 + cost);
        }
    }

    return explored;
}

int AStar::SearchMatrix(const std::vector<std::vector<int>>& graph_matrix, const std::vector<std::vector<double>> &weights, const std::vector<std::vector<double>> &positions, int source, int destination)
{
    parent.assign(graph_matrix.size(), -1);

    // 0 -- untouched; 1 -- to be reviewed; 2 -- visited;
    std::vector<int> used(graph_matrix.size(), 0);
    std::vector<double> gScore(graph_matrix.size(), std::numeric_limits<double>::max());
    std::vector<double> fScore(graph_matrix.size(), std::numeric_limits<double>::max());
    int explored = 0;

    used[source] = 1;
    gScore[source] = 0;
    fScore[source] = std::numeric_limits<double>::max()-1;

    while(1)
    {
        int v = -1;
        for (size_t i = 0; i < graph_matrix.size(); ++i)
        {
            if (used[i] == 1)
            {
                if (v == -1 || fScore[i] < fScore[v])
                    v = i;
            }
        }
        if (v == -1)
            break;
        if (v == destination)
            break;

        used[v] = 2;

        explored++;

        for (size_t i = 0; i < graph_matrix[v].size(); ++i)
        {
            int to = v;
            if (graph_matrix[v][i] == 1)
                to = i;
            else
                continue;
            double cost = weights[v][to];

            if (used[to] == 2)
                continue;

            double tentative_gScore = gScore[v] + cost;

            if (used[to] != 1)
                used[to] = 1;
            else if (tentative_gScore >= gScore[to])
                continue;

            parent[to] = v;
            gScore[to] = tentative_gScore;
            double distance = sqrt((positions[v][0]-positions[to][0]) * (positions[v][0]-positions[to][0])
                    + (positions[v][1]-positions[to][1]) * (positions[v][1]-positions[to][1])
                    + (positions[v][2]-positions[to][2]) * (positions[v][2]-positions[to][2]));
            fScore[to] = gScore[to] + distance*(1 + cost);
        }
    }

    return explored;
}

std::string AStar::GetName()
{
    return "A* search";
}

std::vector<int> AStar::GetParents()
{
    return parent;
}
