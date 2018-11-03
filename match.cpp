#include <string>
#include <vector>
#include "match_context.hpp"
#include "match.hpp"

Match::Match(int line_number,
             std::string file, 
             std::string expression,
             std::string match,
             MatchContext context)
  : line_number(line_number), match(match), context(context) {};
