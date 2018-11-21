#ifndef YAML_CONFIG_H
#define YAML_CONFIG_H
#include <string>
#include "yaml-cpp/yaml.h"

namespace YamlConfig {
  class Config
  {
    public:
      YAML::Node config;
      Config(std::string);
      std::vector<std::string> lookup_expressions_for(std::string);
      static std::string config_path(void);
  };
}

#endif
