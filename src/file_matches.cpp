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
    for (auto m : ent.second)
    {
      m.print();
      std::cout << std::endl;
    }
  }
}

void FileMatches::print_to_csv(std::string output_filename)
{
  std::ofstream myfile;
  myfile.open(output_filename);

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
