#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <limits>
#include <vector>
#include <list>
#include"tsp-dp.h"
using namespace std;

#define DBL_INF  INT_MAX




// Prints binary representation of a subset
void printb(size_t s,int n)
{
	for (int i = n - 1; i >= 0; i--)
		printf("%zu", (s >> i) & 1);
}


// Generates the minimum subdistance for each ending city in each possible
// subset
void build_subsets(dist_vec &subdist, const dist_vec &dist,int n,size_t nset)
{
	// Start with shortest possible tour (starting and ending at the first
	// city)
	subdist[1][0] = 0;

	// Iterate all subsets that include the first city, with size greater
	// than 2 (i.e. every odd bitmask, starting from 3 (dec) or 11 (bin))
	for (size_t s = 3; s < nset; s += 2) {

		// Iterate ending cities (excluding first city)
		for (int j = 1; j < n; j++) {

			if (!(s & (1 << j)))
				continue;

			// Exclude ending city j from subset: S - {j}
			size_t t = s & ~(1 << j);

			// Find minimum sub-distance for this subtour with j as ending city
			for (int i = 0; i < n; i++) {
				if (s & (1 << i) && i != j && subdist[t][i] < DBL_INF)
					subdist[s][j] = min(subdist[s][j], subdist[t][i] + dist[i][j]);
			}
		}
	}
}

// Searches for shortest Hamiltonian cycle
list<int> min_cycle(dist_vec &subdist, const dist_vec &dist, int n, size_t nset)
{
	list<int> cycle(1, 0);
	vector<bool> visited(n, false);

	// Backtracking start with subset that contains all cities
	size_t s = nset - 1;

	// Mark first city as visited
	visited[0] = true;

	for (int i = 0; i < n - 1; i++) {

		int best_j;
		double min_dist = DBL_INF;

		// Find next non-visited city with best sub-distance from
		// previous city in the cycle
		for (int j = 0; j < n; j++) {
			if (!visited[j] && subdist[s][j] + dist[cycle.back()][j] < min_dist) {
				min_dist = subdist[s][j] + dist[cycle.back()][j];
				best_j = j;
			}
		}

		// Mark city as visited and exclude it from the subset
		cycle.push_back(best_j);
		visited[best_j] = true;
		s &= ~(1 << best_j);
	}

	cycle.push_back(0);
	return cycle;
}



void TSP::tspDP(dist_vec dist,int n)
{
	size_t 	nset = 1 << n;
	list<int> cycle;
	double cycle_dist = 0.0;



	// Subset subdistance
	dist_vec subdist(nset, vector<double>(n, DBL_INF));


	build_subsets(subdist, dist,n,nset);
	cycle = min_cycle(subdist, dist, n, nset);

	// Print shortest cycle + distance
	list<int>::const_iterator it;
	cout << "Path is  :  ";
	for (it = cycle.begin(); it != cycle.end(); ++it) {
		printf("%d ", *it);

		if (it != cycle.begin())
			cycle_dist += dist[*it][*prev(it)];
	}
	printf("\nTotal cost is  %0.2f\n", cycle_dist);

}