#ifndef INSERTION_H
#define INSERTION_H

#include "Implementation.h"

class Insertion : public Implementation
{
public:
    Insertion();

    std::vector<int> Sort(const std::vector<int>& data);
    std::string GetName();
};
#endif // INSERTION_H
