#include <string>
#include "match.hpp"
#include "match_candidate.hpp"

MatchCandidate::MatchCandidate(Match match)
  : match(match) {}

void MatchCandidate::mark(void)
{
  _marked = true;
}

bool MatchCandidate::marked(void)
{
  return _marked;
}
