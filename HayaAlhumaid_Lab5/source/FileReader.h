#ifndef LAB_FILEREADER_H
#define LAB_FILEREADER_H

#include <map>
#include <vector>
#include <string>

class FileReader {
public:
    std::vector<std::vector<std::string>> file;
    std::vector<std::vector<std::string>> load_new();
};


#endif 
