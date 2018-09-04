#include "Insertion.h"

Insertion::Insertion()
{

}

std::vector<int> Insertion::Sort(const std::vector<int> &data)
{
    std::vector<int> sorted(data);

    int i, key, j;
    for (i = 1; i < sorted.size(); i++)
    {
        key = sorted[i];
        j = i-1;

        // Move elements of arr[0..i-1], that are
        // greater than key, to one position ahead
        // of their current position
        while (j >= 0 && sorted[j] > key)
        {
            sorted[j+1] = sorted[j];
            j = j-1;
        }
        sorted[j+1] = key;
    }

    return sorted;
}

std::string Insertion::GetName()
{
    return "Insertion";
}
