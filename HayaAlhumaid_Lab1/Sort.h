#ifndef SORT_H
#define SORT_H

#include "Algorithm.h"
#include "Implementation.h"

#include <vector>

class Sort : public Algorithm
{
public:
    Sort();
    ~Sort();

    void Load(std::string filename);
    void Execute();
    void Stats();
    void Select(int id);
    void Display();
    void Save(std::string filename);

private:
    Implementation *implementation;

    std::vector<int> data;
    std::vector<int> sorted;
    long long time_microseconds;
};

#endif // SORT_H
