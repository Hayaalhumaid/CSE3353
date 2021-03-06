// algorithm_lab_2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <ctime>
#include <fstream>


#include "SearchStrategy.h"

using namespace std;

int main(int argc, char *argv[])
{
	int source, destination;

	// uncomment to do N tests
	/*
	const int N = 100;
	int sd_adjacency_matrix[N][5][6];
	int sd_adjacency_list[N][5][6];
	int ds_adjacency_matrix[N][5][6];
	int ds_adjacency_list[N][5][6];
	double sd_adjacency_matrix_norm[N][5][6];
	double sd_adjacency_list_norm[N][5][6];
	double ds_adjacency_matrix_norm[N][5][6];
	double ds_adjacency_list_norm[N][5][6];
	int max_values[N][5]; // Max values for normalizing
	srand(time(0));
	for (int n = 0; n < N; n++)
	{
	*/


		if (argc == 3)
		{
			source = stoi(std::string(argv[1]));
			destination = stoi(std::string(argv[2]));


			SearchStrategy search;
			int N = search.Load(".txt");

			// uncomment to do tests
			/*
			if (n < 0)
			{
				source = 1;
				destination = 5;
			}
			else
			{
				source = destination = 1 + rand() / (RAND_MAX / N);
				while (source == destination)
				{
					destination = 1 + rand() / (RAND_MAX / N);
				}
			}
			*/
			
			for (int i = 1; i <= 6; ++i)
			{
				search.Select(i);
				search.Execute(source, destination);
				search.Save(std::to_string(i));
				search.Stats();
				std::cout << "\n";

				// uncomment to do tests
				/*
				// Collect stats
				// Source -> Destination, Adjacency Matrix
				sd_adjacency_matrix[n][0][i - 1] = search.statistic_data_matrix_sd.path.size(); // nodes in path
				sd_adjacency_matrix[n][1][i - 1] = search.statistic_data_matrix_sd.explored; // nodes explored
				sd_adjacency_matrix[n][2][i - 1] = search.statistic_data_matrix_sd.time; // execution time
				sd_adjacency_matrix[n][3][i - 1] = search.statistic_data_matrix_sd.distance; // distance
				sd_adjacency_matrix[n][4][i - 1] = search.statistic_data_matrix_sd.cost; // cost

				// Source -> Destination, Adjacency List
				sd_adjacency_list[n][0][i - 1] = search.statistic_data_list_sd.path.size(); // nodes in path
				sd_adjacency_list[n][1][i - 1] = search.statistic_data_list_sd.explored; // nodes explored
				sd_adjacency_list[n][2][i - 1] = search.statistic_data_list_sd.time; // execution time
				sd_adjacency_list[n][3][i - 1] = search.statistic_data_list_sd.distance; // distance
				sd_adjacency_list[n][4][i - 1] = search.statistic_data_list_sd.cost; // cost

				// Destination -> Source, Adjacency Matrix
				ds_adjacency_matrix[n][0][i - 1] = search.statistic_data_matrix_ds.path.size(); // nodes in path
				ds_adjacency_matrix[n][1][i - 1] = search.statistic_data_matrix_ds.explored; // nodes explored
				ds_adjacency_matrix[n][2][i - 1] = search.statistic_data_matrix_ds.time; // execution time
				ds_adjacency_matrix[n][3][i - 1] = search.statistic_data_matrix_ds.distance; // distance
				ds_adjacency_matrix[n][4][i - 1] = search.statistic_data_matrix_ds.cost; // cost

				// Destination -> Source, Adjacency List
				ds_adjacency_list[n][0][i - 1] = search.statistic_data_list_ds.path.size(); // nodes in path
				ds_adjacency_list[n][1][i - 1] = search.statistic_data_list_ds.explored; // nodes explored
				ds_adjacency_list[n][2][i - 1] = search.statistic_data_list_ds.time; // execution time
				ds_adjacency_list[n][3][i - 1] = search.statistic_data_list_ds.distance; // distance
				ds_adjacency_list[n][4][i - 1] = search.statistic_data_list_ds.cost; // cost
				*/
			}
			//uncomment to do tests
			/*
			// Collect max values
			// nodes in path
			max_values[n][0] = *max_element(sd_adjacency_matrix[n][0], sd_adjacency_matrix[n][0] + 6);
			max_values[n][0] = max(max_values[n][0], *max_element(sd_adjacency_list[n][0], sd_adjacency_list[n][0] + 6));
			max_values[n][0] = max(max_values[n][0], *max_element(ds_adjacency_matrix[n][0], ds_adjacency_matrix[n][0] + 6));
			max_values[n][0] = max(max_values[n][0], *max_element(ds_adjacency_list[n][0], ds_adjacency_list[n][0] + 6));

			// nodes explored
			max_values[n][1] = *max_element(sd_adjacency_matrix[n][1], sd_adjacency_matrix[n][1] + 6);
			max_values[n][1] = max(max_values[n][1], *max_element(sd_adjacency_list[n][1], sd_adjacency_list[n][1] + 6));
			max_values[n][1] = max(max_values[n][1], *max_element(ds_adjacency_matrix[n][1], ds_adjacency_matrix[n][1] + 6));
			max_values[n][1] = max(max_values[n][1], *max_element(ds_adjacency_list[n][1], ds_adjacency_list[n][1] + 6));

			// execution time
			max_values[n][2] = *max_element(sd_adjacency_matrix[n][2], sd_adjacency_matrix[n][2] + 6);
			max_values[n][2] = max(max_values[n][2], *max_element(sd_adjacency_list[n][2], sd_adjacency_list[n][2] + 6));
			max_values[n][2] = max(max_values[n][2], *max_element(ds_adjacency_matrix[n][2], ds_adjacency_matrix[n][2] + 6));
			max_values[n][2] = max(max_values[n][2], *max_element(ds_adjacency_list[n][2], ds_adjacency_list[n][2] + 6));

			// distance
			max_values[n][3] = *max_element(sd_adjacency_matrix[n][3], sd_adjacency_matrix[n][3] + 6);
			max_values[n][3] = max(max_values[n][3], *max_element(sd_adjacency_list[n][3], sd_adjacency_list[n][3] + 6));
			max_values[n][3] = max(max_values[n][3], *max_element(ds_adjacency_matrix[n][3], ds_adjacency_matrix[n][3] + 6));
			max_values[n][3] = max(max_values[n][3], *max_element(ds_adjacency_list[n][3], ds_adjacency_list[n][3] + 6));

			// cost
			max_values[n][4] = *max_element(sd_adjacency_matrix[n][4], sd_adjacency_matrix[n][4] + 6);
			max_values[n][4] = max(max_values[n][4], *max_element(sd_adjacency_list[n][4], sd_adjacency_list[n][4] + 6));
			max_values[n][4] = max(max_values[n][4], *max_element(ds_adjacency_matrix[n][4], ds_adjacency_matrix[n][4] + 6));
			max_values[n][4] = max(max_values[n][4], *max_element(ds_adjacency_list[n][4], ds_adjacency_list[n][4] + 6));

			// store normolized stats
			for (int j = 0; j < 5; j++)
			{
				for (int i = 0; i < 6; i++)
				{
					sd_adjacency_matrix_norm[n][j][i] = (double)sd_adjacency_matrix[n][j][i] / max_values[n][j];
					sd_adjacency_list_norm[n][j][i] = (double)sd_adjacency_list[n][j][i] / max_values[n][j];
					ds_adjacency_matrix_norm[n][j][i] = (double)ds_adjacency_matrix[n][j][i] / max_values[n][j];
					ds_adjacency_list_norm[n][j][i] = (double)ds_adjacency_list[n][j][i] / max_values[n][j];
				}
			}
			*/
		}
		else
		{
			std::cout << "Input and Destination Nodes are not specified\n";
		}
	// uncomment to do tests
	/*
	}

	//save test data
	std::ofstream data;
	std:ofstream norm;
	data.open("out_data.txt");
	data << "Raw Data Output\n";
	
	norm.open("out_norm_data.txt");
	norm << "Normalized Data Output\n";

	for (int n = 0; n < N; n++)
		{
		data << "\nTest #" << n + 1 << endl;
		data << "\nAdjacency Matrix, Source -> Destination\n";
		data << "\t\tDFS Iter.\tDFS Rec.\tBFS Iter.\tBFS Rec.\tDijkstra\tA*\n";

		norm << "\nTest #" << n + 1 << endl;
		norm << "\nAdjacency Matrix, Source -> Destination\n";
		norm << "\t\tDFS Iter.\tDFS Rec.\tBFS Iter.\tBFS Rec.\tDijkstra\tA*\n";
		
		for (int j = 0; j < 5; j++)
		{
			if (j == 0) {
				data << "Path\t";
				norm << "Path\t";
			}
			else if (j == 1) {
				data << "Explored";
				norm << "Explored";
			}
			else if (j == 2) {
				data << "Time\t";
				norm << "Time\t";
			}
			else if (j == 3) {
				data << "Distance";
				norm << "Distance";
			}
			else if (j == 4) {
				data << "Cost\t";
				norm << "Cost\t";
			}

			for (int i = 0; i < 6; i++)
			{
				data << "\t" << sd_adjacency_matrix[n][j][i];
				norm << "\t" << sd_adjacency_matrix_norm[n][j][i];
			}
			data << "\n";
			norm << "\n";
		}

		data << "\nAdjacency List, Source -> Destination\n";
		data << "\t\tDFS Iter.\tDFS Rec.\tBFS Iter.\tBFS Rec.\tDijkstra\tA*\n";

		norm << "\nAdjacency List, Source -> Destination\n";
		norm << "\t\tDFS Iter.\tDFS Rec.\tBFS Iter.\tBFS Rec.\tDijkstra\tA*\n";

		for (int j = 0; j < 5; j++)
		{
			if (j == 0) {
				data << "Path\t";
				norm << "Path\t";
			}
			else if (j == 1) {
				data << "Explored";
				norm << "Explored";
			}
			else if (j == 2) {
				data << "Time\t";
				norm << "Time\t";
			}
			else if (j == 3) {
				data << "Distance";
				norm << "Distance";
			}
			else if (j == 4) {
				data << "Cost\t";
				norm << "Cost\t";
			}

			for (int i = 0; i < 6; i++)
			{
				data << "\t" << sd_adjacency_list[n][j][i];
				norm << "\t" << sd_adjacency_list_norm[n][j][i];
			}
			data << "\n";
			norm << "\n";
		}

		data << "\nAdjacency Matrix, Destination -> Source\n";
		data << "\t\tDFS Iter.\tDFS Rec.\tBFS Iter.\tBFS Rec.\tDijkstra\tA*\n";

		norm << "\nAdjacency Matrix, Destination -> Source\n";
		norm << "\t\tDFS Iter.\tDFS Rec.\tBFS Iter.\tBFS Rec.\tDijkstra\tA*\n";

		for (int j = 0; j < 5; j++)
		{
			if (j == 0) {
				data << "Path\t";
				norm << "Path\t";
			}
			else if (j == 1) {
				data << "Explored";
				norm << "Explored";
			}
			else if (j == 2) {
				data << "Time\t";
				norm << "Time\t";
			}
			else if (j == 3) {
				data << "Distance";
				norm << "Distance";
			}
			else if (j == 4) {
				data << "Cost\t";
				norm << "Cost\t";
			}

			for (int i = 0; i < 6; i++)
			{
				data << "\t" << ds_adjacency_matrix[n][j][i];
				norm << "\t" << ds_adjacency_matrix_norm[n][j][i];
			}
			data << "\n";
			norm << "\n";
		}

		data << "\nAdjacency List, Destination -> Source\n";
		data << "\t\tDFS Iter.\tDFS Rec.\tBFS Iter.\tBFS Rec.\tDijkstra\tA*\n";

		norm << "\nAdjacency List, Destination -> Source\n";
		norm << "\t\tDFS Iter.\tDFS Rec.\tBFS Iter.\tBFS Rec.\tDijkstra\tA*\n";

		for (int j = 0; j < 5; j++)
		{
			if (j == 0) {
				data << "Path\t";
				norm << "Path\t";
			}
			else if (j == 1) {
				data << "Explored";
				norm << "Explored";
			}
			else if (j == 2) {
				data << "Time\t";
				norm << "Time\t";
			}
			else if (j == 3) {
				data << "Distance";
				norm << "Distance";
			}
			else if (j == 4) {
				data << "Cost\t";
				norm << "Cost\t";
			}

			for (int i = 0; i < 6; i++)
			{
				data << "\t" << ds_adjacency_list[n][j][i];
				norm << "\t" << ds_adjacency_list_norm[n][j][i];
			}
			data << "\n";
			norm << "\n";
		}
		

	}
	data.close();
	norm.close();

	// average normolized results
	double sd_adjacency_matrix_aver[5][6] = { {0,0,0,0,0,0},{ 0,0,0,0,0,0 },{ 0,0,0,0,0,0 },{ 0,0,0,0,0,0 },{ 0,0,0,0,0,0 } };
	double sd_adjacency_list_aver[5][6] = { { 0,0,0,0,0,0 },{ 0,0,0,0,0,0 },{ 0,0,0,0,0,0 },{ 0,0,0,0,0,0 },{ 0,0,0,0,0,0 } };
	double ds_adjacency_matrix_aver[5][6] = { { 0,0,0,0,0,0 },{ 0,0,0,0,0,0 },{ 0,0,0,0,0,0 },{ 0,0,0,0,0,0 },{ 0,0,0,0,0,0 } };
	double ds_adjacency_list_aver[5][6] = { { 0,0,0,0,0,0 },{ 0,0,0,0,0,0 },{ 0,0,0,0,0,0 },{ 0,0,0,0,0,0 },{ 0,0,0,0,0,0 } };

	for (int n = 0; n < N; n++)
	{
		for (int j = 0; j < 5; j++)
		{
			for (int i = 0; i < 6; i++)
			{
				sd_adjacency_matrix_aver[j][i] += sd_adjacency_matrix_norm[n][j][i] / N;
				sd_adjacency_list_aver[j][i] += sd_adjacency_list_norm[n][j][i] / N;
				ds_adjacency_matrix_aver[j][i] += ds_adjacency_matrix_norm[n][j][i] / N;
				ds_adjacency_list_aver[j][i] += ds_adjacency_list_norm[n][j][i] / N;
			}
		}
	}

	// print to file normolized data
	data.open("out_normolized.txt");
	data << "Normolized Data Output\n";

	data << "\nAdjacency Matrix, Source -> Destination\n";
	data << "\t\tDFS Iter.\tDFS Rec.\tBFS Iter.\tBFS Rec.\tDijkstra\tA*\n";

	for (int j = 0; j < 5; j++)
	{
			if (j == 0) {
				data << "Path\t";
			}
			else if (j == 1) {
				data << "Explored";
			}
			else if (j == 2) {
				data << "Time\t";
			}
			else if (j == 3) {
				data << "Distance";
			}
			else if (j == 4) {
				data << "Cost\t";
			}

			for (int i = 0; i < 6; i++)
			{
				data << "\t" << sd_adjacency_matrix_aver[j][i];
			}
			data << "\n";
	}

	data << "\nAdjacency List, Source -> Destination\n";
	data << "\t\tDFS Iter.\tDFS Rec.\tBFS Iter.\tBFS Rec.\tDijkstra\tA*\n";

	for (int j = 0; j < 5; j++)
	{
		if (j == 0) {
			data << "Path\t";
		}
		else if (j == 1) {
			data << "Explored";
		}
		else if (j == 2) {
			data << "Time\t";
		}
		else if (j == 3) {
			data << "Distance";
		}
		else if (j == 4) {
			data << "Cost\t";
		}

		for (int i = 0; i < 6; i++)
		{
			data << "\t" << sd_adjacency_list_aver[j][i];
		}
		data << "\n";
	}

	data << "\nAdjacency Matrix, Destination -> Source\n";
	data << "\t\tDFS Iter.\tDFS Rec.\tBFS Iter.\tBFS Rec.\tDijkstra\tA*\n";

	for (int j = 0; j < 5; j++)
	{
		if (j == 0) {
			data << "Path\t";
		}
		else if (j == 1) {
			data << "Explored";
		}
		else if (j == 2) {
			data << "Time\t";
		}
		else if (j == 3) {
			data << "Distance";
		}
		else if (j == 4) {
			data << "Cost\t";
		}

		for (int i = 0; i < 6; i++)
		{
			data << "\t" << ds_adjacency_matrix_aver[j][i];
		}
		data << "\n";
	}

	data << "\nAdjacency List, Destination -> Source\n";
	data << "\t\tDFS Iter.\tDFS Rec.\tBFS Iter.\tBFS Rec.\tDijkstra\tA*\n";

	for (int j = 0; j < 5; j++)
	{
		if (j == 0) {
			data << "Path\t";
		}
		else if (j == 1) {
			data << "Explored";
		}
		else if (j == 2) {
			data << "Time\t";
		}
		else if (j == 3) {
			data << "Distance";
		}
		else if (j == 4) {
			data << "Cost\t";
		}

		for (int i = 0; i < 6; i++)
		{
			data << "\t" << ds_adjacency_list_aver[j][i];
		}
		data << "\n";
	}
	data.close();
	*/
    return 0;
}

