#include <string>
#include "file_matches.hpp"
#include "match.hpp"

class ExpressionSearch
{
public:
  std::string start_dir;
  std::string language;
  std::vector<std::string> expressions;
  ExpressionSearch(std::string start_dir,
                   std::string language,
                   std::vector<std::string> expressions);
  bool extension_for_lang(std::string lang, std::string ext);
  FileMatches search(void);
  void search_in_file(std::string file_name, std::map<std::string, std::vector<Match>> &file_matches);

private:
  std::map<std::string, std::vector<std::string>> file_extensions =
    {{"ruby",{".rb",
              ".erb"}},
     {"c", {".c"}},
     {"cpp", {".cpp"}}};
};
