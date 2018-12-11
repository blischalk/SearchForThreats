#ifndef MATCH_H
#define MATCH_H
#include <string>
#include <vector>
#include "match_context.hpp"

class Match
{
private:
  std::string calculate_hash(std::string, int, std::string, std::string);

public:
  Match(std::string file_name,
        int line_number,
        std::string expression,
        std::string match,
        MatchContext context);

  std::string file_name;
  int line_number;
  std::string expression;
  std::string match;
  MatchContext context;
  std::string hash;
  void print(void);
};

#endif
