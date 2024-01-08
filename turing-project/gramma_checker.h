#include <set>
#include <string>

#ifndef GRAMMA_CHECKER
#define GRAMMA_CHECKER

int check_input(const std::set<char> &inputSymbol_set, std::string input);
bool check_set(std::string line);
bool check_func(std::string line);

#endif