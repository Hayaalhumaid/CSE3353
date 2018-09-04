#include "Bubble.h"

#include <vector>

Bubble::Bubble()
{

}

std::vector<int> Bubble::Sort(const std::vector<int> &data)
{
    std::vector<int> sorted(data);
    for (int i = 0; i < sorted.size()-1; ++i)
    {
        bool flag = false;
        for (int j = 0; j < sorted.size()-1-i; ++j)
        {
            if (sorted[j] > sorted[j+1])
            {
                swap(sorted[j], sorted[j+1]);
                flag = true;
            }

        }
        if (!flag)
            break;
    }
    return sorted;
}

std::string Bubble::GetName()
{
    return "Bubble";
}

void Bubble::swap(int &a, int &b)
{
    int c = a;
    a = b;
    b = c;
}
