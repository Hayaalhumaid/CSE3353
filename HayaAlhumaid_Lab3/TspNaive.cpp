#include <iostream>
#include"tsp-dp.h"

using namespace std;

double TSP::travllingSalesmanProblem(const dist_vec& graph, int s, vector<int> &Path)
{
	// store all vertex apart from source vertex 
	vector<int> vertex;
	
	for (int i = 0; i < n; i++)
	if (i != s)
		vertex.push_back(i);

	// store minimum weight Hamiltonian Cycle. 
	int min_path = INT_MAX;
	do {

		// store current Path weight(cost) 
		int current_pathweight = 0;

		// compute current path weight 
		int k = s;
		for (int i = 0; i < vertex.size(); i++) {
			current_pathweight += graph[k][vertex[i]];
			k = vertex[i];
		}
		current_pathweight += graph[k][s];
	
		// update minimum
		if (min_path>current_pathweight)
			Path = vertex;
		min_path = min(min_path, current_pathweight);

	} while (next_permutation(vertex.begin(), vertex.end()));

	return min_path*1.0;
}
