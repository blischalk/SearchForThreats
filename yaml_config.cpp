#include <string>
#include "yaml_config.hpp"
#include "yaml-cpp/yaml.h"

namespace YamlConfig {
  Config::Config(std::string config_file) {
    config = YAML::LoadFile(config_file);
  };

  std::vector<std::string> Config::lookup_expressions_for(std::string language)
  {
    std::vector<std::string> expressions;
    expressions = config[language].as<std::vector<std::string>>();

    return expressions;
  };

  std::string Config::config_path(void) {
    const std::string home = getenv("HOME");
    const std::string config_file = home + "/sft_config.yaml";
    return config_file;
  }
};
