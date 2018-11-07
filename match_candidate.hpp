#ifndef MATCH_CANDIDATE_H
#define MATCH_CANDIDATE_H
#include <string>
#include <vector>
#include "file_matches.hpp"
#include "match.hpp"
#include "match_candidate.hpp"
class MatchCandidate
{
  private:
    bool _marked = false;
  public:
    Match match;
    MatchCandidate(Match match);
    void mark(void);
    bool marked(void);
};

#endif
