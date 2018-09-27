#include <iostream>
#include <string>


#include "SearchStrategy.h"

using namespace std;

int main(int argc, char *argv[])
{
    int source = 1, destination = 2;
    if (argc == 3)
    {
        source = stoi(std::string(argv[1]));
        destination = stoi(std::string(argv[2]));
    }

    SearchStrategy search;
    search.Load(".txt");
    for (int i = 1; i <= 6; ++i)
    {
        search.Select(i);
        search.Execute(source, destination);
        search.Save(std::to_string(i));
        search.Stats();
        std::cout << "\n";
    }

    return 0;
}
