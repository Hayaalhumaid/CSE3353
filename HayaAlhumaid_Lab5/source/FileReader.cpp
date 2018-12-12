#include "FileReader.h"
#include <fstream>
#include <sstream>
#include <iostream>

std::vector<std::vector<std::string>> FileReader::load_new() {
    std::ifstream file_path("data/positions.txt");
    std::string line, token;
    int count = 0;

    if(file_path){
        while(getline(file_path,line)){
            std::stringstream ssi(line);
            std::vector<std::string> temp_;
            while (getline(ssi, token, ','))
            {
                temp_.push_back(token);
            }
            file.push_back(temp_);
            count++;
        }
    }
    else{
        std::cerr << "Error reading file" <<  std::endl;
        exit(EXIT_FAILURE);
    }

    file_path.close();

    return file;
}