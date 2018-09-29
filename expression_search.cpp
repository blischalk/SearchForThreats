#include <boost/filesystem.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include "expression_search.hpp"

using namespace boost::filesystem;

ExpressionSearch::ExpressionSearch(std::vector<std::string> expressions) :
  expressions(expressions)
{};

void ExpressionSearch::search(void)
{
  std::ifstream fileText;
  std::string line;

  recursive_directory_iterator end;
  for (recursive_directory_iterator it("./"); it != end; ++it) {
    std::string extension = boost::filesystem::extension(*it);
    if (extension == ".rb") {
      std::cout << "found ruby file!" << std::endl;
      fileText.open(it->path().string());
      if (fileText.good())
        {
          while (getline(fileText, line))
            {
              for (std::size_t i=0; i < expressions.size(); i++)
                {

                  std::regex e(expressions[i]);
                  bool match = regex_search(line, e);
                  if (match) {
                    std::cout << expressions[i] << std::endl;
                    std::cout << "Match found! " << std::endl;
                  }
                }
            }
        }
      fileText.close();
    }
  }
}
