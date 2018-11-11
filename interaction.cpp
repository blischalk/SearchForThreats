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
  std::cout << "(i) - Ignore finding in future review" << std::endl;
  std::cout << "(m) - Mark finding for review" << std::endl;
  std::cout << "(s) - Skip finding" << std::endl;
}

void Interaction::init_ignore(void)
{
  const std::string default_ignore_filename = ".sft_ignore";
  std::cout << "Use " << default_ignore_filename << " (y or n)?" << std::endl;
  char user_selection;
  user_selection = std::cin.get();
  std::string ignore_filename;

retry:
  switch (user_selection)
  {
    case 'y':
      std::cout << "Using " << default_ignore_filename << std::endl;;
      ignore_filename = default_ignore_filename;
      break;
    case 'n':
      std::cout << "Enter file name: " << std::endl;
      std::cin >> ignore_filename;
      break;
    default:
      std::cout << "Please make a valid selection " << std::endl;
      goto retry;
      break;
  }
  std::cin.get();
}

FileMatches Interaction::review_matches(void)
{
  bool run = true;
  char user_selection;

  init_ignore();

  for (auto &mc : match_candidates)
  {
    if (!run)
    {
      break;
    }

retry:
    mc.match.print();

    std::cout << "What would you like to do? (press q to quit)"
      << std::endl;
    print_match_menu();
    user_selection = std::cin.get();

    switch (user_selection)
    {
      case 'm':
        std::cout << "Marking!" << std::endl;
        mc.mark();
        std::cout << "Marked is: " << mc.marked() << std::endl;
        break;
      case 's':
        std::cout << "Skipping!" << std::endl;
        break;
      case 'q':
        run = false;
        break;
      default:
        std::cout << "Please make a valid selection " << std::endl;
        goto retry;
        break;
    }
    std::cin.get();
  }

  std::map<std::string, std::vector<Match>> file_matches;
  for(auto mc : match_candidates)
  {
    if (mc.marked())
    {
      if (file_matches.find(mc.match.file_name) == file_matches.end())
      {
        std::vector<Match> file_match_collection;
        file_matches[mc.match.file_name] = file_match_collection;
      }

      file_matches[mc.match.file_name].push_back(mc.match);
    }
  }
  FileMatches fm = FileMatches(file_matches);
  return fm;
}

FileMatches Interaction::start(void)
{
  std::cout << "Welcome to interactive SFT!"
    << std::endl;

  return review_matches();

}

