#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

#include "Sort.h"

// This function generates data sets for sets
void GenerateDataSets()
{
    for (int n = 10; n <= 100000; n *= 10)
    {
        // Random values
        std::ofstream fout_rand("Random"+std::to_string(n)+".txt");
        for (int i = 0; i < n; ++i)
            fout_rand << rand()%n+1 << " ";

        // Reversed values
        std::ofstream fout_reversed("Reversed"+std::to_string(n)+".txt");
        for (int i = n; i >= 1; --i)
            fout_reversed << i << " ";

        // Unique values
        std::ofstream fout_unique("Unique"+std::to_string(n)+".txt");
        std::vector<int> data_unique(n); // Create and fill a vector with unique values: 1, 2, 3...
        for (int i = 0; i < n; ++i)
            data_unique[i] = i+1;
        for (int i = 0; i < n/2; ++i) // "Shake" them randomly
        {
            int a, b, c; // a, b --  indicies for swap; c -- temp variable for swap
            a = rand()%n;
            b = rand()%n;
            c = data_unique[a];
            data_unique[a] = data_unique[b];
            data_unique[b] = c;
        }
        for (int i = 0; i < n; ++i)
            fout_unique << data_unique[i] << " ";

        // Partial sort values
        std::ofstream fout_partial("Partial"+std::to_string(n)+".txt");
        std::vector<int> data_partial(n); // Create a vector with random values
        for (int i = 0; i < n; ++i)
            data_partial[i] = rand()%n+1;
        // a function from algorithm library which performs partial sort
        std::partial_sort(data_partial.begin(), data_partial.begin()+(n*0.7), data_partial.end());
        for (int i = 0; i < n; ++i)
            fout_partial << data_partial[i] << " ";

        if (n == 10)
            n *= 10;
    }
}

int main()
{
    //GenerateDataSets();
    Sort sort;
    for (int i = 1; i <= 3; ++i)
    {
        sort.Select(i);
        for (int n = 10; n <= 10000; n *= 10)
        {
            std::cout << "Random" << std::endl;
            sort.Load("Random"+std::to_string(n)+".txt");
            sort.Execute();
            sort.Stats();
            //sort.Display();
            std::cout << std::endl;

            std::cout << "Reversed" << std::endl;
            sort.Load("Reversed"+std::to_string(n)+".txt");
            sort.Execute();
            sort.Stats();
            //sort.Display();
            std::cout << std::endl;

            std::cout << "Unique" << std::endl;
            sort.Load("Unique"+std::to_string(n)+".txt");
            sort.Execute();
            sort.Stats();
            //sort.Display();
            std::cout << std::endl;

            std::cout << "Partial" << std::endl;
            sort.Load("Partial"+std::to_string(n)+".txt");
            sort.Execute();
            sort.Stats();
            //sort.Display();
            std::cout << std::endl;

            if (n == 10)
                n *= 10;
        }
        std::cout << "\n---------------------------------------\n\n";
    }
    return 0;
}
