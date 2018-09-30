#include <string>
#include "cxxopts.hpp"
#include "expression_search.hpp"
#include "yaml_config.hpp"

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

  std::string start_dir = argv[1];
  std::string language  = argv[2];

  if (language != "ruby")
    {
      std::cout << "Only ruby is currently supported" << std::endl;
      exit(1);
    }

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
