#ifndef FILE_MATCHES_H
#define FILE_MATCHES_H
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "match.hpp"
class FileMatches
{
  public:
    std::map<std::string, std::vector<Match>> file_matches;
    FileMatches(std::map<std::string, std::vector<Match>> file_matches);
    void print(void);
    void print_to_csv(std::string);
};
#endif
