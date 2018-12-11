#include <algorithm>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <sys/stat.h>
#include "ignore_file.hpp"
#include "match.hpp"
#include "match_candidate.hpp"
#include "yaml-cpp/yaml.h"

IgnoreFile::IgnoreFile()
{
  const std::string default_ignore_filename = ".sft_ignore";
  std::cout << "Use " << default_ignore_filename << " (y or n)?" << std::endl;
  char user_selection;
  user_selection = std::cin.get();
  std::cin.get();

  const std::string home = getenv("HOME");
  _ignore_filename = home + "/";
  std::string tmp;

retry:
  switch (user_selection)
  {
    case 'y':
      std::cout << "Using " << default_ignore_filename << std::endl;;
      _ignore_filename.append(default_ignore_filename);
      break;
    case 'n':
      std::cout << "Enter file name: " << std::endl;
      std::cin >> tmp;
      std::cout << "You entered: " << tmp << std::endl;
      _ignore_filename.append(tmp);
      std::cout << "Ignore file is: " << _ignore_filename << std::endl;
      break;
    default:
      std::cout << "Please make a valid selection " << std::endl;
      goto retry;
      break;
  }

  load_or_create();
}

bool IgnoreFile::ignore_exists(const std::string& name) {
  struct stat buffer;
  return (stat (name.c_str(), &buffer) == 0);
}

void IgnoreFile::load_or_create(void)
{
  if (!ignore_exists(_ignore_filename))
  {
    std::ofstream _ignore_file (_ignore_filename);
    _ignore_file.close();
  }

  _ignore_file = YAML::LoadFile(_ignore_filename);
}

void IgnoreFile::write(std::vector<MatchCandidate> mcs)
{
  //std::vector<YAML::Emitter> emitters;
  YAML::Emitter out;
  out << YAML::BeginMap;
  out << YAML::Key << "ignores";
  out << YAML::Value;
  out << YAML::BeginSeq;

  std::for_each(mcs.begin(), mcs.end(), [&](MatchCandidate mc){
      if (mc.ignored() == true)
      {
        out << YAML::BeginMap;
        out << YAML::Key << "file_name";
        out << YAML::Value << mc.match.file_name;
        out << YAML::Key << "line_number";
        out << YAML::Value << mc.match.line_number;
        out << YAML::Key << "expression";
        out << YAML::Value << mc.match.expression;
        out << YAML::Key << "match";
        out << YAML::Value << mc.match.match;
        out << YAML::Key << "hash";
        out << YAML::Value << mc.match.hash;
        out << YAML::EndMap;
      }
  });

  out << YAML::EndSeq;
  out << YAML::EndMap;

  std::ofstream fout(_ignore_filename);
  fout << out.c_str();
  fout.close();

}

std::vector<std::string> IgnoreFile::hashes(void)
{
  std::vector<std::string> hashes;
  auto ignores = _ignore_file["ignores"].as<std::vector<std::map<std::string, std::string>>>();

  std::for_each(ignores.begin(), ignores.end(), [&](std::map<std::string, std::string> ignore){
    hashes.push_back(ignore["hash"]);
  });

  return hashes;
}
