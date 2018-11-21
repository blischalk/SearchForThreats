#include <iostream>
#include <stdexcept>
#include <string>
#include <sys/stat.h>
#include "ignore_file.hpp"
#include "yaml-cpp/yaml.h"

IgnoreFile::IgnoreFile()
{
  const std::string default_ignore_filename = ".sft_ignore";
  std::cout << "Use " << default_ignore_filename << " (y or n)?" << std::endl;
  char user_selection;
  user_selection = std::cin.get();

retry:
  switch (user_selection)
  {
    case 'y':
      std::cout << "Using " << default_ignore_filename << std::endl;;
      _ignore_filename = default_ignore_filename;
      break;
    case 'n':
      std::cout << "Enter file name: " << std::endl;
      std::cin >> _ignore_filename;
      break;
    default:
      std::cout << "Please make a valid selection " << std::endl;
      goto retry;
      break;
  }
  std::cin.get();

  load_or_create();
}

bool IgnoreFile::ignore_exists(const std::string& name) {
  struct stat buffer;
  return (stat (name.c_str(), &buffer) == 0);
}

void IgnoreFile::load_or_create(void)
{
  if (ignore_exists(_ignore_filename))
  {
    _ignore_file = YAML::LoadFile(_ignore_filename);
  } else {
    throw std::runtime_error( "ignore file hasn't been created" );
  }
}

