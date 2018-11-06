#include <iostream>
//#include <cstdio>
//#include <cstdlib>
//#include <algorithm>
//#include <cmath>
//#include <limits>
#include"tsp-dp.h"
//#define D_SCL_SECURE_NO_WARNINGS
using namespace std;
//
//double min_len = numeric_limits<double>::infinity();
//
//
//// Returns the full cycle length for the current permutation of cities
//double route_len(const int cities[], dist_vec dist,int n)
//{
//	double len = 0;
//	for (int i = 1; i <= n; i++)
//		len += dist[cities[i - 1]][cities[i % n]];
//
//	return len;
//}
//
//
//
//// Recursively checks the cycle cost of all (n - 1)! city permutations
//void TSP::calculate(int cities[], int route[], dist_vec dist,int i )
//{
//	if (i == n) {
//		double len = route_len(cities, dist,n);
//		if (len < min_len) {
//			//copy(cities, cities + n, route);
//			for (int temp = 0; temp < n; temp++)
//				route[temp] = cities[temp];
//			min_len = len;
//		}
//
//		return;
//	}
//
//	for (int j = i; j < n; j++) {
//		swap(cities[i], cities[j]);
//		calculate(cities, route, dist, i + 1);
//		swap(cities[i], cities[j]);
//	}
//	
//}
//
//void TSP::tspNaive(int cities[], int route[], dist_vec dist){
//	double cost=0;
//	calculate(cities, route, dist, 1);
//	for (int i = 1; i <=n; i++)
//		cost += dist[cities[i - 1]][cities[i % n]];
//
//	printf("Total cost is  %0.2f\n", cost);
//}




















//double TSP::tspNaive(const dist_vec& cities, int pos, int visited, dist_vec& state, vector<int>& cycle)
//{
//	std::vector<int>::iterator it;
//	
//	if (visited == ((1 << cities.size()) - 1))
//		return cities[pos][0]; // return to starting city
//
//	if (state[pos][visited] != INT_MAX)
//		return state[pos][visited];
//
//
//	for (int i = 0; i < cities.size(); ++i)
//	{
//		
//		// can't visit ourselves unless we're ending & skip if already visited
//		if (i == pos || (visited & (1 << i)))
//			continue;
//		//
//		int distance = cities[pos][i] + tspNaive(cities, i, visited | (1 << i), state, cycle);
//		cout << pos << endl;
//		if (distance < state[pos][visited])
//		{
//			state[pos][visited] = distance;
//			
//		}
//	}
//	it = std::find(cycle.begin(), cycle.end(), pos);
//	
//	return state[pos][visited];
//}


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
