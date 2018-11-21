#ifndef MATCH_H
#define MATCH_H
#include <string>
#include <vector>
#include "match_context.hpp"

class Match
{
  public:
    std::string file_name;
    int line_number;
    std::string expression;
    std::string match;
    MatchContext context;
    void print(void);

    Match(std::string file_name,
        int line_number,
        std::string expression,
        std::string match,
        MatchContext context);
};

#endif
