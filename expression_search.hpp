#include <string>
#include "match.hpp"
#include "types.hpp"

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
  void search(void);
  void print_match(FileMatches fm);

private:
  std::map<std::string, std::vector<std::string>> file_extensions =
    {{"ruby",{".rb",
              ".erb"}},
     {"c", {".c"}},
     {"cpp", {".cpp"}}};
};
