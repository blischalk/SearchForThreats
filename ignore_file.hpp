#ifndef IGNORE_FILE_H
#define IGNORE_FILE_H
#include <string>
#include "yaml-cpp/yaml.h"
class IgnoreFile
{
  public:
    IgnoreFile();
  private:
    YAML::Node _ignore_file;
    std::string _ignore_filename;
    void load_or_create(void);
    bool ignore_exists(const std::string&);
};

#endif
