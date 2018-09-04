#include "Merge.h"

#include <vector>

Merge::Merge()
{

}

std::vector<int> Merge::Sort(const std::vector<int> &data)
{
    std::vector<int> sorted(data);

    MergeSort(sorted, 0, sorted.size()-1);

    return sorted;
}

void Merge::MergeMerge(std::vector<int>& data, int low, int high, int mid)
{
    // We have low to mid and mid+1 to high already sorted
    int i, j, k;
    std::vector<int> temp(high-low+1);
    i = low;
    k = 0;
    j = mid + 1;

    // Merge the two parts into temp
    while (i <= mid && j <= high)
    {
        if (data[i] < data[j])
        {
            temp[k] = data[i];
            k++;
            i++;
        }
        else
        {
            temp[k] = data[j];
            k++;
            j++;
        }
    }

    // Insert all the remaining values from i to mid into temp
    while (i <= mid)
    {
        temp[k] = data[i];
        k++;
        i++;
    }

    // Insert all the remaining values from j to high into temp
    while (j <= high)
    {
        temp[k] = data[j];
        k++;
        j++;
    }

    // Assign sorted data stored in temp to data
    for (i = low; i <= high; i++)
    {
        data[i] = temp[i-low];
    }
}


void Merge::MergeSort(std::vector<int>& data, int low, int high)
{
    int mid;
    if (low < high)
    {
        mid=(low+high)/2;
        // Split the data into two half
        MergeSort(data, low, mid);
        MergeSort(data, mid+1, high);

        // Merge them to get sorted output
        MergeMerge(data, low, high, mid);
    }
}

std::string Merge::GetName()
{
    return "Merge";
}
