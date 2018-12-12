#ifndef LAB_ALGOHANDLER_H
#define LAB_ALGOHANDLER_H

#include "Graph.h"
#include "FileReader.h"

class Algorithms;

class AlgoHandler {
private:
    Graph g;
    FileReader f;

	Algorithms* algo = nullptr;
public:
	enum class AlgoType
	{
		TSP = 1, 
		TABU, 
		GENETIC,
		//LASTFACT, 
		SA, 
		PSO
	};

	AlgoHandler() = default;
    ~AlgoHandler();
    void load_new();
    void select_algo(AlgoType);
	void run_algo();

};

#endif //LAB_ALGOHANDLER_H
