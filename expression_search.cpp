#include <boost/filesystem.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <string>
#include "expression_search.hpp"
#include "file_matches.hpp"
#include "match.hpp"

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

FileMatches ExpressionSearch::search()
{
  std::ifstream file_text;
  std::string line;
  std::string file_name;
  std::map<std::string, std::vector<Match>> file_matches;

  recursive_directory_iterator end;
  for (recursive_directory_iterator it(start_dir); it != end; ++it) {
    std::string extension = boost::filesystem::extension(*it);
    file_name = it->path().string();

    if (extension_for_lang(language, extension)) {
      std::cout << "\033[1;35mSearching file: \033[0m"
                << file_name
                << "\n"
                << std::endl;

      file_text.open(it->path().string());

      std::vector<std::string> mem_file;
      std::vector<Match> file_match_collection;
      file_matches[file_name] = file_match_collection;

      if (file_text.good())
        {
          while (getline(file_text, line))
            {
              mem_file.push_back(line);
            }
        }

      file_text.close();

      for (std::size_t line_number = 0; line_number < mem_file.size(); line_number++)
        {
          for (std::size_t i=0; i < expressions.size(); i++)
            {

              std::regex e(expressions[i]);
              bool match = regex_search(mem_file.at(line_number), e);
              if (match) {
                MatchContext c = MatchContext(mem_file, line_number, 3, 3);
                Match m   = Match(file_name, line_number, expressions[i], mem_file.at(line_number), c);
                file_matches[file_name].push_back(m);
              }
            }
        }

    }
  }
  FileMatches fm = FileMatches(file_matches);
  return fm;
}
