#include <cryptopp/sha.h>
#include <cryptopp/filters.h>
#include <cryptopp/hex.h>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <sys/stat.h>
#include "ignore_file.hpp"
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

void IgnoreFile::ignore(MatchCandidate mc)
{
  CryptoPP::SHA1 sha1;
  std::string source = mc.match.file_name + std::to_string(mc.match.line_number) + mc.match.expression + mc.match.match;  //This will be randomly generated somehow
  std::string hash = "";
  CryptoPP::StringSource(source, true, new CryptoPP::HashFilter(sha1, new CryptoPP::HexEncoder(new CryptoPP::StringSink(hash))));

  std::cout << "The hash is: " << hash << std::endl;

  YAML::Emitter out;
  out << YAML::BeginMap;
  out << YAML::Key << "File Name: ";
  out << YAML::Value << mc.match.file_name;
  out << YAML::Key << "Line Number: ";
  out << YAML::Value << mc.match.line_number;
  out << YAML::Key << "Expression: ";
  out << YAML::Value << mc.match.expression;
  out << YAML::Key << "Match: ";
  out << YAML::Value << mc.match.match;
  out << YAML::Key << "Hash: ";
  out << YAML::Value << hash;
  out << YAML::EndMap;

  std::ofstream fout(_ignore_filename);
  fout << out.c_str();
  fout.close();

}