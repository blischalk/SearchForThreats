#include <boost/filesystem.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <mutex>
#include <regex>
#include <string>
#include <thread>
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

void ExpressionSearch::search_in_file(std::string file_name, std::map<std::string, std::vector<Match>> &file_matches, std::mutex &_lock)
{
  std::ifstream file_text;
  std::string line;
  std::string extension = boost::filesystem::extension(file_name);

  if (extension_for_lang(language, extension))
  {
    std::cout << "\033[1;35mSearching file: \033[0m"
      << file_name
      << "\n"
      << std::endl;

    file_text.open(file_name);

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
          _lock.lock();
          file_matches[file_name].push_back(m);
          _lock.unlock();
        }
      }
    }
  }
}

FileMatches ExpressionSearch::search()
{
  std::vector<std::string> file_names;
  std::map<std::string, std::vector<Match>> file_matches;

  recursive_directory_iterator end;
  for (recursive_directory_iterator it(start_dir); it != end; ++it) {
    file_names.push_back(it->path().string());
  }

  int processor_count = 4;
  unsigned int size   = file_names.size();
  int group_size      = size / processor_count;
  int remainder       = size % processor_count;
  std::vector<std::thread> threadList;
  std::mutex _lock;

  // Check that we have files to search
  // And that we have at least one per processor
  if (size > 0 && group_size > 0)
  {
    for (int i=0; i < processor_count; i++)
    {
      unsigned char begin_offset = i;
      unsigned char end_offset   = i + group_size;
      if (i == (processor_count - 1) && remainder > 0)
      {
        end_offset = end_offset + remainder;
      }

      threadList.push_back(std::thread([&]()
      {

        std::for_each(file_names.begin() + begin_offset,
                      file_names.begin() + end_offset,
                      [&](std::string file_name)
        {
          std::cout << "Multi-thread search. Searching file: " << file_name << std::endl;
          search_in_file(file_name, file_matches, _lock);
        });
      }));
    }

    std::cout << "Blocking on search completion" << std::endl;
    std::for_each(threadList.begin(),threadList.end(), std::mem_fn(&std::thread::join));
  } else {
    std::for_each(file_names.begin(), file_names.end(), [&](std::string file_name)
    {
      search_in_file(file_name, file_matches, _lock);
    });
  }

  FileMatches fm = FileMatches(file_matches);
  return fm;
}
