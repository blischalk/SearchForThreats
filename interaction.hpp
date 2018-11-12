#ifndef INTERACTION_H
#define INTERACTION_H
#include "file_matches.hpp"
#include "match.hpp"
#include "match_candidate.hpp"
class Interaction
{
  public:
    Interaction(FileMatches file_matches);
    void print_match_menu(void);
    FileMatches start(void);
    FileMatches review_matches(void);
  private:
    std::vector<MatchCandidate> match_candidates;
    void flatten_matches(FileMatches file_matches);
};

#endif
