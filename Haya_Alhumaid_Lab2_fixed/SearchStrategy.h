#ifndef SEARCHSTRATEGY_H
#define SEARCHSTRATEGY_H

#include "Algorithm.h"
#include "SearchImpl.h"

#include <vector>

class SearchStrategy : public Algorithm
{
public:
    SearchStrategy();
    ~SearchStrategy();

    void Load(std::string filetype);
    void Execute(int source, int destination);
    void Stats();
    void Select(int id);
    void Display();
    void Save(std::string filename);

private:
    int selected_id;
    SearchImpl *implementation;

    std::vector<std::pair<int, int>> random_source_destination;

    std::vector<std::vector<int>> graph_list;
    std::vector<std::vector<int>> graph_matrix;

    std::vector<std::vector<double>> weights;
    std::vector<std::vector<double>> positions;

    struct ExecutionData
    {
        std::vector<int> path;
        double cost, distance;
        long long time;
        int explored;
    };
    std::vector<ExecutionData> statistic_data_list_sd, statistic_data_matrix_sd;
    std::vector<ExecutionData> statistic_data_list_ds, statistic_data_matrix_ds;

    void _CalcPathData(ExecutionData& data, const std::vector<int> &parents, int source, int destination);
};

#endif // SEARCHSTRATEGY_H
