#include <string>
#include "cxxopts.hpp"
#include "expression_search.hpp"
#include "yaml_config.hpp"

const std::vector<std::string> supported_languages = {"ruby"};

int main(int argc, char* argv[])
{
  cxxopts::Options options("sft [path...] [language ruby|python]",
                           "Look for threats in an application");

  options.add_options()
    ("h,help", "Show help") ;

  auto result = options.parse(argc, argv);

  if (result.count("help") || argc < 3)
    {
      std::cout << options.help({"", "Group"}) << std::endl;
      exit(0);
    }

  if (!std::any_of(supported_languages.begin(),
                   supported_languages.end(),
                   [argv](std::string str){return argv[2] == str;}) )
    {
      std::cout << argv[2]
                << " is not currently supported"
                << std::endl;
      exit(1);
    }

  std::string start_dir = argv[1];
  std::string language  = argv[2];

  std::vector<std::string> expressions;
  YamlConfig::Config cfg = YamlConfig::Config(YamlConfig::DEFAULT_CONFIG);
  expressions = cfg.lookup_expressions_for(language);

  if (expressions.size() > 0)
    {
      ExpressionSearch es = ExpressionSearch(start_dir, language, expressions);
      es.search();
    }

  return 0;
}
