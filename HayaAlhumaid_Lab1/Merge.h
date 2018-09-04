#ifndef MERGE_H
#define MERGE_H

#include "Implementation.h"

class Merge : public Implementation
{
public:
    Merge();

    std::vector<int> Sort(const std::vector<int>& data);
    std::string GetName();

private:
    // A function to merge the two half into a sorted data
    void MergeMerge(std::vector<int>& data, int low, int high, int mid);
    // A function to split array into two parts
    void MergeSort(std::vector<int>& data, int low, int high);

};
#endif // MERGE_H
