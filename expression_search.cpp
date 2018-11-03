#include <boost/filesystem.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <string>
#include "expression_search.hpp"

using namespace boost::filesystem;


ExpressionSearch::ExpressionSearch(std::string start_dir,
                                   std::string language,
                                   std::vector<std::string> expressions) :
  start_dir(start_dir),
  language(language),
  expressions(expressions) {};

bool ExpressionSearch::extension_for_lang(std::string lang,
                                          std::string ext)
{
  std::map<std::string, std::vector<std::string>>::iterator it;
  if((it = file_extensions.find(lang)) != file_extensions.end())
    {
      std::vector<std::string> extensions = it->second;
      if (std::find(extensions.begin(),
                    extensions.end(),
                    ext)
          != extensions.end())
        {
          return true;
        }
    }
  return false;
}

void ExpressionSearch::search(void)
{
  std::ifstream fileText;
  std::string line;

  recursive_directory_iterator end;
  for (recursive_directory_iterator it(start_dir); it != end; ++it) {
    std::string extension = boost::filesystem::extension(*it);
    if (extension_for_lang(language, extension)) {
      std::cout << "\033[1;35mSearching file: \033[0m"
                << it->path().string()
                << "\n"
                << std::endl;
      fileText.open(it->path().string());
      std::vector<std::string> mem_file;

      if (fileText.good())
        {
          while (getline(fileText, line))
            {
              mem_file.push_back(line);
            }
        }

      fileText.close();

      for (std::size_t line_number = 0; line_number < mem_file.size(); line_number++)
        {
          for (std::size_t i=0; i < expressions.size(); i++)
            {

              std::regex e(expressions[i]);
              bool match = regex_search(mem_file.at(line_number), e);
              if (match) {
                std::cout << "\033[1;31mFound a match on line: \033[0m"
                          << line_number
                          << std::endl;
                std::cout << "\033[1;32mMatching expression: \033[0m"
                          << expressions[i]
                          << std::endl;
                std::cout << "\033[1;33mLine contents are: \033[0m"
                          << mem_file.at(line_number)
                          << "\n"
                          << std::endl;
                print_with_context(mem_file, line_number, 3, 3);
                std::cout << std::endl;
              }
            }
        }
    }
  }
}

void ExpressionSearch::print_with_context(std::vector<std::string> mem_file,
    int line_number,
    int preroll,
    int postroll)
{
  std::size_t length = mem_file.size();
  int proposed_start = line_number - preroll;
  int proposed_end   = line_number + postroll;
  int start          = proposed_start < 0 ? 0 : proposed_start;
  int end            = proposed_end > (int)(length - 1) ? (int)(length - 1) : proposed_end;

  while (start <= end)
  {
    std::cout << "line " << (start + 1) << ": ";
    std::cout << mem_file.at(start)
              << std::endl;
    start++;
  }

}
