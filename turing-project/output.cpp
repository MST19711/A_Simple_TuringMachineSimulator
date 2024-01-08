#include "output.h"
#include "TM.h"
#include <iostream>
#include <string>

bool gramma_error(int addr, std::string input) {
    std::cerr << "==================== ERR ====================\n";
    std::cerr << "error: Symbol \"" << input[addr]
              << "\" in input is not defined in the set of input symbol\n";
    std::cerr << "Input: " << input << std::endl;
    std::cerr << "       ";
    for (int i = 0; i < addr; i++) {
        std::cerr << " ";
    }
    std::cerr << "^\n";
    std::cerr << "==================== END ====================\n";
    return true;
}

bool gramma_noerror(std::string input) {
    std::cout << "==================== RUN ====================\n";
    return true;
}
bool print_help() {
    std::cout << "usage: turing [-v|--verbose] [-h|--help] <tm> <input>\n";
    return true;
}