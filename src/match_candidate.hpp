#ifndef MATCH_CANDIDATE_H
#define MATCH_CANDIDATE_H
#include <string>
#include <vector>
#include "match.hpp"
#include "match_candidate.hpp"
class MatchCandidate
{
  private:
    bool _marked  = false;
    bool _ignored = false;
  public:
    Match match;
    MatchCandidate(Match match);
    void ignore(void);
    bool ignored(void);
    void mark(void);
    bool marked(void);
};

#endif
