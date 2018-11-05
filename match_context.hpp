#ifndef MATCH_CONTEXT_H
#define MATCH_CONTEXT_H
#include <string>
#include <vector>

class MatchContext
{
  public:
    std::vector<std::string> lines;
    MatchContext(std::vector<std::string> mem_file,
                 int line_number,
                 int preroll,
                 int postroll);
    int start;
    int end;
  private:
    std::vector<std::string> mem_file;
    int line_number;
    int preroll;
    int postroll;
};

#endif
