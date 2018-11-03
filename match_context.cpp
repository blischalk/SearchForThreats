#include <string>
#include <vector>
#include "match_context.hpp"

MatchContext::MatchContext(std::vector<std::string> mem_file,
                           int line_number,
                           int preroll,
                           int postroll)
  : mem_file(mem_file),
    line_number(line_number),
    preroll(preroll),
    postroll(postroll) {
      std::size_t length = mem_file.size();
      int proposed_start = line_number - preroll;
      int proposed_end   = line_number + postroll;
      int start          = proposed_start < 0 ? 0 : proposed_start;
      int end            = proposed_end > (int)(length - 1) ? (int)(length - 1) : proposed_end;

      while (start <= end)
      {
        lines.push_back(mem_file.at(start));
        start++;
      }
    
    };
