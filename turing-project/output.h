#include "TM.h"
#include <iostream>
#include <string>

#ifndef ERR_OUTPUT
#define ERR_OUTPUT

bool gramma_error(int addr, std::string input);
bool gramma_noerror(std::string input);
bool print_help();

#endif