#include<iostream>
#include<vector>
#include<queue>
using namespace std;
typedef vector<vector<double> > dist_vec;
class TSP{
public:
	//double tspNaive(const dist_vec& cities, int pos, int visited, dist_vec& state, vector<int>& cycle);
	double travllingSalesmanProblem(const dist_vec& graph, int s, vector<int> &Path);
	void TSP::calculate(int cities[], int route[], dist_vec dist, int i=1);
	int n;
	
	void tspDP(dist_vec dist, int n);
	TSP()
	{
	 
	}

};