#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <string>
#include <vector>

class Algorithm
{
public:
    virtual ~Algorithm() {}

    virtual void Load(std::string filename) = 0;
    virtual void Execute(int source, int destination) = 0;
    virtual void Stats() = 0;
    virtual void Select(int id) = 0;
    virtual void Display() = 0;
    virtual void Save(std::string filename) = 0;


    //virtual void Configure() = 0;
};

#endif // ALGORITHM_H
