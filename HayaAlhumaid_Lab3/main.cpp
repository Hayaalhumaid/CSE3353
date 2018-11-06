#include<iostream>
#include<istream>
#include<ostream>
#include <fstream>
#include <iomanip>
#include<string>
#include<vector>
#include <chrono> 
#include<set>
#include<queue>
using namespace std::chrono;
#include"tsp-dp.h"
typedef vector<vector<double> > dist_vec;
using namespace std;





int min(int a, int b){

	return a < b ? a : b;

}
size_t split(const std::string &txt, std::vector<std::string> &strs, char ch)
{
	size_t pos = txt.find(ch);
	size_t initialPos = 0;
	strs.clear();

	// Decompose statement
	while (pos != std::string::npos) {
		strs.push_back(txt.substr(initialPos, pos - initialPos));
		initialPos = pos + 1;

		pos = txt.find(ch, initialPos);
	}

	// Add the last one
	strs.push_back(txt.substr(initialPos, min(pos, txt.size()) - initialPos + 1));
	if (strs.size() == 1 && strs[0] == "")
	{
		strs.clear();
		strs.push_back(txt);
	}

	return strs.size();
}

int GetNumberOfLines(string filename)
{
	fstream infile;
	string line;
	std::vector<std::string> v;
	infile.open(filename);
	int count = 0;
	if (infile.is_open())
	{
		while (getline(infile, line))
		{
			count++;
		}
		infile.close();
	}
	return count;

}


void ReadFile(string filename, dist_vec &dist,int element)
{
	fstream infile;
	string line;
	std::vector<std::string> v;
	infile.open(filename);
	int count = 0;
	if (infile.is_open())
	{
		while (getline(infile, line))
		{
			split(line,v,',');
			for (int i = 0; i < element; i++)
			{
				dist[count][i] = stoi(v[i]);
			}
			count++;
		}
		infile.close();
	}
	

}

void print_route(vector<int> cities, int n)
{
	cout << "0 " ;
	for (int i = 0; i < n-1; i++)
		printf("%d ", cities[i]);
	cout << "0 ";
	printf("\n");
}
int main(int argc, char **argv)
{
	int n;
	ofstream datafile;
	datafile.open("ExecutionTime.txt");
	datafile << "Nodes\t" << "Naive    " << "DP    " << endl;

		string filename = "graph2.txt";
		n = GetNumberOfLines(filename);
		dist_vec dist(n, vector<double>(n));
		ReadFile(filename, dist, n);
	
		TSP t;

		t.n = n;
		vector<int> cycle;
		
		cout << "Naive Algorithm " << endl;
		auto startNaive = high_resolution_clock::now();
	   
		dist_vec state(n, vector<double>(1<<n, INT_MAX));
	

		cout << "Naive Total Cost : " << t.travllingSalesmanProblem(dist, 0, cycle) << endl;

		auto stopnaive = high_resolution_clock::now();
		cout << "Path is : ";
		print_route(cycle, n);
		auto durationNaive = duration_cast<microseconds>(stopnaive - startNaive);
		cout << "Naive Algorithm Execution Time : " << durationNaive.count()<<" miliseconds" << endl;
		cout << "\nDynamic  Programming" << endl;
		auto startDP = high_resolution_clock::now();
		t.tspDP(dist, n);
		auto stopDP = high_resolution_clock::now();


		
		auto durationDP = duration_cast<microseconds>(stopDP - startDP);
		datafile << n << "     " << (durationNaive.count())<<"       " << durationDP.count() << endl;
		cout << "Dynamic Programming Algorithm Execution Time : " << durationDP.count() << " miliseconds\n" << endl;
	return 0;
}


