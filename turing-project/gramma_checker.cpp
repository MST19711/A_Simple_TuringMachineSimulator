#include "gramma_checker.h"
#include <iostream>
#include <sstream>
#include <string>

int check_input(const std::set<char> &inputSymbol_set, std::string input) {
    for (int i = 0; i < input.length(); i++) {
        if (inputSymbol_set.count(input[i]) == 0) {
            return i;
        }
    }
    return -1;
}

bool check_set(std::string line) {
    int brace = 0;
    bool meet_equ = false;
    for (int i = 3; i < line.length(); i++) {
        if (line[i] == '=')
            meet_equ = true;
        if (line[i] != '=' and line[i] != ' ' and not meet_equ)
            return 0;
        if (line[i] == '{')
            brace++;
        if (line[i] == '}')
            brace--;
        if (brace > 0) {
            if (line[i] == ' ') {
                bool comma = false;
                int j = i;
                for (; line[j] == ' '; j--)
                    ;
                if (line[j] == ',' or line[j] == '}' or line[j] == '{')
                    comma = true;
                for (j = i; line[j] == ' '; j++)
                    ;
                if (line[j] == ',' or line[j] == '}' or line[j] == '{')
                    comma = true;
                if (comma == false)
                    return 0;
            }
        }
    }
    return brace == 0;
}
bool check_func(std::string line) {
    int end = line.length() - 1;
    for (; line[end] == ' ' and end >= 0; end--)
        ;
    std::string L = line.substr(0, end + 1);
    std::stringstream ss(L);
    std::string word;
    int counter = 0;
    while (std::getline(ss, word, ' '))
        counter++;
    // std::cerr << counter << "\n";
    return counter == 5;
}