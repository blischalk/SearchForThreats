#include <cryptopp/sha.h>
#include <cryptopp/filters.h>
#include <cryptopp/hex.h>
#include <iostream>
#include <string>
#include <vector>
#include "match_context.hpp"
#include "match.hpp"

Match::Match(std::string file_name,
             int line_number,
             std::string expression,
             std::string match,
             MatchContext context)
  : file_name(file_name),
    line_number(line_number),
    expression(expression),
    match(match),
    context(context)
{
  hash = calculate_hash(file_name, line_number, expression, match);
};

std::string Match::calculate_hash(std::string file_name,
                                  int line_number,
                                  std::string expression,
                                  std::string match)
{
  CryptoPP::SHA1 sha1;
  std::string source = file_name + std::to_string(line_number) + expression + match;  //This will be randomly generated somehow
  std::string hash = "";
  CryptoPP::StringSource(source, true, new CryptoPP::HashFilter(sha1, new CryptoPP::HexEncoder(new CryptoPP::StringSink(hash))));

  std::cout << "The hash is: " << hash << std::endl;
  return hash;
}

void Match::print(void)
{
  std::cout << "Match from file: "
    << file_name
    << std::endl;

  std::cout << "\033[1;32mMatched expression: \033[0m"
    << expression
    << std::endl;

  std::cout << "\033[1;33mMatched line "
    << line_number
    << ": \033[0m"
    << match
    << "\n"
    << std::endl;

  int context_line_number = context.start;
  for (auto line : context.lines)
  {
    std::cout << context_line_number << ": ";
    std::cout << line
      << std::endl;
    context_line_number++;
  }

  std::cout << std::endl;
}
