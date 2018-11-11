#include <string>
#include "yaml-cpp/yaml.h"

namespace YamlConfig {
  const std::string DEFAULT_CONFIG = "~/sft_config.yaml";
  class Config
  {
  public:
    YAML::Node config;
    Config(std::string);
    std::vector<std::string> lookup_expressions_for(std::string);
  };
}
