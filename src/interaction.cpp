#include <algorithm>
#include <climits>
#include <iostream>
#include <string>
#include "file_matches.hpp"
#include "ignore_file.hpp"
#include "interaction.hpp"
#include "match.hpp"
#include "match_candidate.hpp"

Interaction::Interaction(FileMatches file_matches)
{
  match_candidates = file_matches.flatten();
}

void Interaction::print_match_menu(void)
{
  std::cout << "(i) - Ignore finding in future review" << std::endl;
  std::cout << "(m) - Mark finding for review" << std::endl;
  std::cout << "(s) - Skip finding" << std::endl;
}

bool Interaction::should_ignore_prev(void)
{
  std::cout << "Ignore previously ignored matches? (y or n)" << std::endl;
  char user_selection;
  bool response = true;

  retry:
  user_selection = std::cin.get();

  switch (user_selection)
    {
    case 'y':
      response = true;
      break;
    case 'n':
      response = false;
      break;
    default:
      std::cout << "Please make a valid selection " << std::endl;
      goto retry;
      break;
    }
  std::cin.get();
  return response;
}

FileMatches Interaction::review_matches(IgnoreFile ignore_f,
                                        const bool ignore_prev)
{
  bool run = true;
  char user_selection;
  std::vector<std::string> prev_ignore_hashes = ignore_f.hashes();

  for (auto &mc : match_candidates)
  {
    if (!run)
      {
        break;
      }

    if (ignore_prev && std::any_of(prev_ignore_hashes.begin(),
                                   prev_ignore_hashes.end(),
                                   [=](std::string h) {
                                     return h == mc.match.hash;
                                   }))
      {
        continue;
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
      case 'i':
        std::cout << "Ignore match:" << std::endl;
        mc.ignore();
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

  IgnoreFile ignore_f;
  bool ignore_prev = should_ignore_prev();
  FileMatches fm = review_matches(ignore_f, ignore_prev);
  ignore_f.write(match_candidates);

  return fm;

}
