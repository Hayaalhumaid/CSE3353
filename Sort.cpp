#include "Sort.h"

#include "Bubble.h"
#include "Merge.h"
#include "Insertion.h"

#include <chrono>
#include <iostream>
#include <fstream>

Sort::Sort() // initialize values
    : implementation(nullptr), time_microseconds(0)
{}

Sort::~Sort()
{
    delete implementation;
}

void Sort::Load(std::string filename)
{
    // clear data vector
    data.clear();
    std::ifstream fin(filename); // open file
    while (!fin.eof()) // read until we reach end of file
    {
        data.push_back(0);
        fin >> data.back();
    }
    data.pop_back();
}

void Sort::Execute()
{
    using namespace std::chrono;
    high_resolution_clock::time_point t1 = high_resolution_clock::now(); // remember starting time
    sorted = implementation->Sort(data);
    high_resolution_clock::time_point t2 = high_resolution_clock::now(); // remember finishing time
    auto elapsed = duration_cast<microseconds>(t2-t1); // calculate elapsed time
    time_microseconds = elapsed.count(); // convert to integer
}

void Sort::Stats()
{
    std::cout << "Algorithm name: " << implementation->GetName() << " sort" << std::endl;
    std::cout << "Time elapsed (microseconds): " << time_microseconds << std::endl;
    std::cout << "Number of records: " << data.size()<< std::endl;
}

void Sort::Select(int id)
{
    delete implementation;
    switch (id)
    {
    case 1:
        implementation = new Bubble;
        break;
    case 2:
        implementation = new Merge;
        break;
    case 3:
        implementation = new Insertion;
        break;
    default:
        implementation = nullptr;
        break;
    }
}

void Sort::Display()
{
    for (int d : sorted) // across all values in vector
        std::cout << d << " ";
    std::cout << std::endl;
}

void Sort::Save(std::string filename)
{
    std::ofstream fout(filename);
    for (int d : sorted) // across all values in vector
        fout << d << " ";
}
