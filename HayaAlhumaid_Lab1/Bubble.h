#ifndef BUBBLE_H
#define BUBBLE_H

#include "Implementation.h"

class Bubble : public Implementation
{
public:
    Bubble();

    std::vector<int> Sort(const std::vector<int>& data);
    std::string GetName();

private:
    void swap(int &a, int &b);
};

#endif // BUBBLE_H
