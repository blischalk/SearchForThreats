#include <string>
#include "cxxopts.hpp"
#include "expression_search.hpp"
#include "interaction.hpp"
#include "file_matches.hpp"
#include "yaml_config.hpp"

const std::vector<std::string> supported_languages =
  {"ruby", "c", "cpp"};

struct mode {
  bool interactive = false;
  std::string output_filename;
  std::string format;
} mode;

void option_validation(int argc, char* argv[])
{
  cxxopts::Options options("sft [path...] [language ruby|python]",
      "Look for threats in an application");

  options.add_options()
    ("f,format", "Output file format: (only csv currently supported)", cxxopts::value<std::string>()->default_value("csv"))
    ("o,output", "Output filename", cxxopts::value<std::string>()->default_value("sft_report"))
    ("i,interactive", "Interactive Mode")
    ("h,help", "Show Help") ;

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

  if (result.count("interactive"))
  {
    std::cout << "Interactive mode selected." << std::endl;
    mode.interactive = true;
  }

  if (result.count("output"))
  {
    std::string output_filename;
    mode.output_filename = output_filename = result["output"].as<std::string>();
    std::cout << "Writing output to file: " << output_filename << std::endl;

    std::string format;
    mode.format = format = result["format"].as<std::string>();
    std::cout << "Formatting output as: " << format << std::endl;
  }

}

std::vector<std::string> config_expressions(std::string language)
{
  std::vector<std::string> expressions;
  YamlConfig::Config cfg = YamlConfig::Config(YamlConfig::DEFAULT_CONFIG);
  expressions = cfg.lookup_expressions_for(language);
  return expressions;
}

int main(int argc, char* argv[])
{

  option_validation(argc, argv);

  std::string start_dir = argv[1];
  std::string language  = argv[2];
  std::vector<std::string> expressions;
  expressions = config_expressions(language);

  if (expressions.size() > 0)
  {
    ExpressionSearch es = ExpressionSearch(start_dir, language, expressions);
    FileMatches fm = es.search();

    if (mode.interactive)
    {
      Interaction i = Interaction(fm);
      fm = i.start();
    }

    std::cout << "Results of expression searching: " << std::endl;
    fm.print();
    
    std::cout << "Sending results to CSV file." << std::endl;
    fm.print_to_csv(mode.output_filename);
  }


  return 0;
}
