
#include "SearchStrategy.h"

#include "RecursiveDFS.h"
#include "IterativeDFS.h"
#include "RecursiveBFS.h"
#include "IterativeBFS.h"
#include "Dijkstra.h"
#include "AStar.h"

#include <fstream>
#include <sstream>
#include <chrono>
#include <iostream>
#include <algorithm>
#include <numeric>

SearchStrategy::SearchStrategy()
    : selected_id(0), implementation(nullptr)
{

}

SearchStrategy::~SearchStrategy()
{
    delete implementation;
}

int SearchStrategy::Load(std::string filetype)
{
    graph_list.clear();
    graph_matrix.clear();
    weights.clear();
    positions.clear();

    // Read graph structure
	std::ifstream graph_file; // ("graph" + filetype);
	graph_file.open("graph" + filetype);
    std::string line;
    while (std::getline(graph_file, line))
    {
        std::istringstream line_stream(line);
        std::string token;
        std::getline(line_stream, token, ',');
        int node = stoi(token);

        while(std::getline(line_stream, token, ','))
        {
            int child = stoi(token);

            int max_id = std::max(node, child);
            if (max_id > graph_list.size())
            {
                graph_list.resize(max_id);
                graph_matrix.resize(max_id, std::vector<int>(max_id, 0));
                for (size_t i = 0; i < graph_matrix.size(); ++i)
                    graph_matrix[i].resize(max_id, 0);
            }

            graph_list[node-1].push_back(child-1); // -1 because program indexes start at 0
            graph_matrix[node-1][child-1] = 1;
        }
    }

    weights.assign(graph_list.size(), std::vector<double>(graph_list.size(), 0));
    positions.assign(graph_list.size(), {0, 0, 0});

    // read the weights and positions
	std::ifstream weights_file;
	weights_file.open("weights" + filetype);
    while (std::getline(weights_file, line))
    {
        std::istringstream line_stream(line);
        std::string token;

        std::getline(line_stream, token, ',');
        int node = stoi(token);
        std::getline(line_stream, token, ',');
        int child = stoi(token);
        std::getline(line_stream, token, ',');
        double weight = stod(token);

        weights[node-1][child-1] = weight;
    }

	std::ifstream positions_file;
	positions_file.open("positions" + filetype);
    while (std::getline(positions_file, line))
    {
        std::istringstream line_stream(line);
        std::string token;

        std::getline(line_stream, token, ',');
        int node = stoi(token);
        std::getline(line_stream, token, ',');
        double x = stod(token);
        std::getline(line_stream, token, ',');
        double y = stod(token);
        std::getline(line_stream, token, ',');
        double z = stod(token);

        positions[node-1] = {x, y, z};
    }

    //for (int i = 0; i < 100; ++i)
    //    random_source_destination.push_back(std::make_pair(rand()%graph_list.size(), rand()%graph_list.size()));
	return graph_list.size();
}

void SearchStrategy::Execute(int source, int destination)
{
    if (!implementation)
        return;

    //statistic_data_list_sd.assign(random_source_destination.size()+1, ExecutionData());
    //statistic_data_matrix_sd.assign(random_source_destination.size()+1, ExecutionData());
    //statistic_data_list_ds.assign(random_source_destination.size()+1, ExecutionData());
    //statistic_data_matrix_ds.assign(random_source_destination.size()+1, ExecutionData());

    source--;
    destination--;

    using namespace std::chrono;
    //for (size_t i = 0; i < random_source_destination.size(); ++i)
    //{
        {
            high_resolution_clock::time_point t1 = high_resolution_clock::now(); // remember starting time
            statistic_data_list_sd.explored = implementation->SearchList(graph_list, weights, positions, source, destination);
            high_resolution_clock::time_point t2 = high_resolution_clock::now(); // remember finishing time
            auto elapsed = duration_cast<microseconds>(t2-t1); // calculate elapsed time
            statistic_data_list_sd.time = elapsed.count() + 1; // convert to integer

            std::vector<int> parents_list = implementation->GetParents();
            _CalcPathData(statistic_data_list_sd, parents_list, source, destination);

            t1 = high_resolution_clock::now();
            statistic_data_matrix_sd.explored = implementation->SearchMatrix(graph_matrix, weights, positions, source, destination);
            t2 = high_resolution_clock::now();
            elapsed = duration_cast<microseconds>(t2-t1);
            statistic_data_matrix_sd.time = elapsed.count() + 1;

            std::vector<int> parents_matrix = implementation->GetParents();
            _CalcPathData(statistic_data_matrix_sd, parents_matrix, source, destination);
        }
        {
            high_resolution_clock::time_point t1 = high_resolution_clock::now(); // remember starting time
            statistic_data_list_ds.explored = implementation->SearchList(graph_list, weights, positions, source, destination);
            high_resolution_clock::time_point t2 = high_resolution_clock::now(); // remember finishing time
            auto elapsed = duration_cast<microseconds>(t2-t1); // calculate elapsed time
            statistic_data_list_ds.time = elapsed.count() + 1; // convert to integer

            std::vector<int> parents_list = implementation->GetParents();
            _CalcPathData(statistic_data_list_ds, parents_list, source, destination);

            t1 = high_resolution_clock::now();
            statistic_data_matrix_ds.explored = implementation->SearchMatrix(graph_matrix, weights, positions, source, destination);
            t2 = high_resolution_clock::now();
            elapsed = duration_cast<microseconds>(t2-t1);
            statistic_data_matrix_ds.time = elapsed.count() + 1;

            std::vector<int> parents_matrix = implementation->GetParents();
            _CalcPathData(statistic_data_matrix_ds, parents_matrix, source, destination);
        }

        //source = random_source_destination[i].first;
        //destination = random_source_destination[i].second;
    //}
}

void SearchStrategy::Stats()
{
    const ExecutionData& data = statistic_data_list_sd;
    std::cout << implementation->GetName() << " | Source -> Destination | Adjancency list" << std::endl;
    std::cout << "Path: ";
    for (size_t i = 0; i < data.path.size(); ++i)
        std::cout << data.path[i]+1 << " ";
    std::cout << " -- number of nodes: " << data.path.size() << std::endl;
    std::cout << "Cost of the path: " << data.cost << std::endl;
    std::cout << "Distance of the path: " << data.distance << std::endl;
    std::cout << "Number of explored nodes: " << data.explored << std::endl;
    std::cout << "Execution time (nanoseconds): " << data.time << std::endl;
}

void SearchStrategy::Select(int id)
{
    delete implementation;
    selected_id = id;
    switch (selected_id)
    {
    case 1:
        implementation = new RecursiveDFS;
        break;
    case 2:
        implementation = new IterativeDFS;
        break;
    case 3:
        implementation = new RecursiveBFS;
        break;
    case 4:
        implementation = new IterativeBFS;
        break;
    case 5:
        implementation = new Dijkstra;
        break;
    case 6:
        implementation = new AStar;
        break;
    default:
        implementation = nullptr;
        break;
    }
}

void SearchStrategy::Display()
{

}

void SearchStrategy::Save(std::string filename)
{
    std::ofstream fout(filename+".txt");

    fout << implementation->GetName() << "\n\n";

    for (const auto &data : {statistic_data_list_sd, statistic_data_matrix_sd, statistic_data_list_ds, statistic_data_matrix_ds})
    {
        // Uncomment to output raw stats
      //  for (size_t i = 1; i < random_source_destination.size(); ++i)
      //  {
      //      fout << statistic_data_list_sd[i].path.size() << "\t";
      //      fout << statistic_data_list_sd[i].explored << "\t";
      //      fout << statistic_data_list_sd[i].time << "\t";
      //      fout << statistic_data_list_sd[i].distance << "\t";
      //      fout << statistic_data_list_sd[i].cost << "\t\n";
      //  }

        // Outputs MIN/MAX and average of stats
		/*
        fout << "Nodes in path (min/avr/max)\t";
        fout << std::min_element(data.begin(), data.end()-1, [](const ExecutionData &a, const ExecutionData &b){return a.path.size()<b.path.size();})->path.size() << "\t";
        fout << (double)std::accumulate(data.begin(), data.end()-1, 0, [](double a, const ExecutionData & b){return a + b.path.size();}) / (data.size()-1) << "\t";
        fout << std::max_element(data.begin(), data.end()-1, [](const ExecutionData &a, const ExecutionData &b){return a.path.size()<b.path.size();})->path.size() << "\n";

        fout << "Nodes explored (min/avr/max)\t";
        fout << std::min_element(data.begin(), data.end()-1, [](const ExecutionData &a, const ExecutionData &b){return a.explored<b.explored;})->explored << "\t";
        fout << (double)std::accumulate(data.begin(), data.end()-1, 0, [](double a, const ExecutionData & b){return a + b.explored;}) / (data.size()-1) << "\t";
        fout << std::max_element(data.begin(), data.end()-1, [](const ExecutionData &a, const ExecutionData &b){return a.explored<b.explored;})->explored << "\n";

        fout << "Execution time (min/avr/max)\t";
        fout << std::min_element(data.begin(), data.end()-1, [](const ExecutionData &a, const ExecutionData &b){return a.time<b.time;})->time << "\t";
        fout << (double)std::accumulate(data.begin(), data.end()-1, 0, [](double a, const ExecutionData & b){return a + b.time;}) / (data.size()-1) << "\t";
        fout << std::max_element(data.begin(), data.end()-1, [](const ExecutionData &a, const ExecutionData &b){return a.time<b.time;})->time << "\n";

        fout << "Path distance (min/avr/max)\t";
        fout << std::min_element(data.begin(), data.end()-1, [](const ExecutionData &a, const ExecutionData &b){return a.distance<b.distance;})->distance << "\t";
        fout << (double)std::accumulate(data.begin(), data.end()-1, 0, [](double a, const ExecutionData & b){return a + b.distance;}) / (data.size()-1) << "\t";
        fout << std::max_element(data.begin(), data.end()-1, [](const ExecutionData &a, const ExecutionData &b){return a.distance<b.distance;})->distance << "\n";

        fout << "Path cost (min/avr/max)\t";
        fout << std::min_element(data.begin(), data.end()-1, [](const ExecutionData &a, const ExecutionData &b){return a.cost<b.cost;})->cost << "\t";
        fout << (double)std::accumulate(data.begin(), data.end()-1, 0, [](double a, const ExecutionData & b){return a + b.cost;}) / (data.size()-1) << "\t";
        fout << std::max_element(data.begin(), data.end()-1, [](const ExecutionData &a, const ExecutionData &b){return a.cost<b.cost;})->cost << "\n";

        fout << "\n--------------------------------\n\n";
		*/
    }

}

void SearchStrategy::_CalcPathData(SearchStrategy::ExecutionData &data, const std::vector<int> &parents, int source, int destination)
{
    // This part constructs the path out of array of parents
    data.path.clear();
    data.path.push_back(destination);
    for (int i = parents[destination]; i != source; i = parents[i])
    {
        data.path.push_back(i);
        if (i == -1) // there is no path
        {
            data.path.clear();
            break;
        }
    }
    data.path.push_back(source);
    std::reverse(data.path.begin(), data.path.end());


    data.cost = 0;
    for (size_t i = 0; i < data.path.size()-1; ++i)
        data.cost += weights[data.path[i]][data.path[i+1]];
    data.distance = 0;
    for (size_t i = 0; i < data.path.size()-1; ++i)
    {
        int v = i, to = i + 1;
        double distance = sqrt((positions[v][0]-positions[to][0]) * (positions[v][0]-positions[to][0])
                + (positions[v][1]-positions[to][1]) * (positions[v][1]-positions[to][1])
                + (positions[v][2]-positions[to][2]) * (positions[v][2]-positions[to][2]));
        data.distance += distance;
    }
}
