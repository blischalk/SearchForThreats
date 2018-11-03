#ifndef MATCH_H
#define MATCH_H
#include <string>
#include <vector>
#include "match_context.hpp"

class Match
{
  public:
    int line_number;
    std::string file;
    std::string expression;
    std::string match;
    MatchContext context;

    Match(int line_number,
        std::string file, 
        std::string expression,
        std::string match,
        MatchContext context);
};

#endif
