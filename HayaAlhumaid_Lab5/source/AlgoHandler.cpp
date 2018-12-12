#include "AlgoHandler.h"

#include "TSPProto.h"
#include "TabuProto.h"
#include "GAProto.h"
#include "SAProto.h"
#include "PSOProto.h"

void AlgoHandler::load_new() 
{
    f.load_new();

    for(size_t i = 0; i < f.file.size(); ++i) 
	{
        g.map[stoi(f.file[i][0])].operator=({stof(f.file[i][1]), stof(f.file[i][2]), stof(f.file[i][3])});
    }

    g.cost_calculation();
}

void AlgoHandler::select_algo(AlgoType type) 
{
	delete algo;
	algo = nullptr;

    if (type == AlgoType::TSP)
	{
        algo = new TSPProto(&g);
    }
    else if (type == AlgoType::TABU)
	{
		algo = new TabuProto(&g);
    }
    else if (type == AlgoType::GENETIC)
	{
		algo = new GAProto(&g);
    }
	else if (type == AlgoType::SA)
	{
		algo = new SAProto(&g);
	}
	else if (type == AlgoType::PSO)
	{
		algo = new PSOProto(&g);
	}
}

void AlgoHandler::run_algo()
{
	if (!algo)
		return;
	algo->exec();
	algo->out();
}

AlgoHandler::~AlgoHandler() 
{
	delete algo;
}
