#include <climits>
#include <iostream>
#include <string>
#include "file_matches.hpp"
#include "interaction.hpp"
#include "match.hpp"
#include "match_candidate.hpp"

Interaction::Interaction(FileMatches file_matches)
{
  flatten_matches(file_matches);
}

void Interaction::flatten_matches(FileMatches file_matches)
{
  for (auto const &ent : file_matches.file_matches)
  {
    for (auto m : ent.second)
    {
      MatchCandidate mc = MatchCandidate(m);
      match_candidates.push_back(mc);
    }
  }
}

void Interaction::print_match_menu(void)
{
  std::cout << "(m) - Mark finding for review" << std::endl;
  std::cout << "(s) - Skip finding" << std::endl;
}

void Interaction::start(void)
{
  std::cout << "Welcome to interactive SFT!"
    << std::endl;

  bool run = true;
  char user_selection;

  while (run) {
    for (auto mc : match_candidates)
    {
      if (!run)
      {
        break;
      }

      mc.match.print();

      std::cout << "What would you like to do? (press q to quit)"
        << std::endl;
      print_match_menu();

      user_selection = std::cin.get();

      switch (user_selection)
      {
        case 'm':
          std::cout << "Marking!" << std::endl;
          mc.marked = true;
          break;
        case 's':
          std::cout << "Skipping!" << std::endl;
          break;
        case 'q':
          run = false;
          break;
        default:
          break;
      }
      std::cin.get();
    }
    run = false;
  }

  std::cout << "Good bye!"
    << std::endl;
}

