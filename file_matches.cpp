#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include "file_matches.hpp"

FileMatches::FileMatches(std::map<std::string, std::vector<Match>> file_matches) : file_matches(file_matches) {};

void FileMatches::print(void)
{
  for (auto const &ent : file_matches)
  {
    std::cout << "\033[1;31mResults for File: \033[0m"
      << ent.first
      << std::endl;

    for (auto m : ent.second)
    {
      std::cout << "\033[1;31mFound a match on line: \033[0m"
        << m.line_number
        << std::endl;

      std::cout << "\033[1;32mMatching expression: \033[0m"
        << m.expression
        << std::endl;

      for (auto line : m.context.lines)
      {
        std::cout << line
          << std::endl;
      }

      std::cout << std::endl;

      std::cout << "\033[1;33mLine contents are: \033[0m"
        << m.match
        << "\n"
        << std::endl;

      std::cout << std::endl;
    }
  }
}

void FileMatches::print_to_csv(void)
{
  std::ofstream myfile;
  myfile.open("report.csv");

  myfile << "Source File, Detected Expression, Line Number, Line Contents, In Context,\n";
  for (auto const &ent : file_matches)
  {
    for (auto m : ent.second)
    {
      myfile << ent.first << ",";
      myfile << m.expression << ",";
      myfile << m.line_number << ",";
      myfile << m.match << ",";

      myfile << "\"";
      for (auto line : m.context.lines)
      {
        myfile << line << "\n";
      }
      myfile << "\"";
      myfile << "\n";

    }
  }

  myfile.close();
}
