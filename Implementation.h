#ifndef IMPLEMENTATION_H
#define IMPLEMENTATION_H

#include <vector>
#include <string>

// Abstract class for all sorting algorithms
// Is used in Srategy pattern
class Implementation
{
public:
    // function accepts vector of input data and returns a vector of sorted values
    virtual std::vector<int> Sort(const std::vector<int>& data) = 0;
    virtual std::string GetName() = 0;
};

#endif // IMPLEMENTATION_H
