#include <string>
#include "cxxopts.hpp"
#include "expression_search.hpp"
#include "yaml_config.hpp"

int main(int argc, char* argv[])
{
  cxxopts::Options options("sft [path...] [language ruby|python]",
                           "Look for threats in an application");

  options.add_options()
    ("h,help", "Show help")
    ("a,add", "Add threat")
    ("r,remove", "Remove threat")
    ("v,vuln-type", "Vulnerability type",
     cxxopts::value<std::vector<std::string>>(), "VULNTYPE");

  auto result = options.parse(argc, argv);

  if (result.count("help") || argc < 3)
    {
      std::cout << options.help({"", "Group"}) << std::endl;
      exit(0);
    }

  if (result.count("v"))
    {
      auto& vv = result["v"].as<std::vector<std::string>>();
      std::cout << "Vulnerability types:" << std::endl;
      for (const auto& v : vv)
        {
          std::cout << v << std::endl;
        }
    }

  std::vector<std::string> expressions;
  YamlConfig::Config cfg = YamlConfig::Config(YamlConfig::DEFAULT_CONFIG);
  expressions = cfg.lookup_expressions_for("ruby");

  if (expressions.size() > 0)
    {
      ExpressionSearch es = ExpressionSearch(expressions);
      es.search();
    }

  return 0;
}
