#include <string>

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
  void print_with_context(std::vector<std::string> memfile,
                          int line_number,
                          int preroll,
                          int postroll);

private:
  std::map<std::string, std::vector<std::string>> file_extensions =
    {{"ruby",{".rb",
              ".erb"}},
     {"c", {".c"}},
     {"cpp", {".cpp"}}};
};
