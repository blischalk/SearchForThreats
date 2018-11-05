#ifndef MATCH_CANDIDATE_H
#define MATCH_CANDIDATE_H
#include <string>
#include <vector>
#include "file_matches.hpp"
#include "match.hpp"
#include "match_candidate.hpp"
class MatchCandidate
{
  public:
    Match match;
    bool marked = false;
    MatchCandidate(Match match);
};

#endif
