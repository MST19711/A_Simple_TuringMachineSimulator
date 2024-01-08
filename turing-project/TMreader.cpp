#include "TMreader.h"
#include "gramma_checker.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

std::string pre_handle(std::string &line) {
    int i = 0;
    std::string temp;
    while (i < line.length() and line[i] != ';')
        temp.push_back(line[i]), i++;
    while (temp.back() == ' ')
        temp.pop_back();
    // std::cerr << temp << "\n";
    return temp;
}
int str2int(std::string str) {
    int ret = 0;
    for (int i = 0; i < str.length(); i++) {
        ret += str[i] - '0';
        ret *= 10;
    }
    ret /= 10;
    return ret;
}

bool read_TM(std::string path, TuringMachine &turningMachine) {
    std::fstream fin;
    fin.open(path, std::ios::in);
    if (!fin) {
        std::cerr << "Cannot open the file" << std::endl;
        return 0;
    }
    int N, sets = 0;
    char Bsym;
    std::string line, q0;
    std::set<std::string> Q, F;
    std::set<char> S, G;
    while (std::getline(fin, line)) {
        if (line[0] == '\0' or line[0] == ';' or line[0] == '\n')
            continue;
        if (line[0] == '#') {
            line = pre_handle(line);
            // std::cerr << line << "\n";
            sets++;
            if (!check_set(line)) {
                std::cerr << "syntax error\n"; // set\n";
                // std::cerr << line << "\n";
                return 0;
            }
            if (line[1] == 'Q') {
                int i = 0;
                for (; line[i] != '{'; i++)
                    ;
                line = line.substr(i + 1, line.size() - 2 - i);
                // std::cerr << line << "\n";
                std::string state;
                std::stringstream ss(line);
                while (std::getline(ss, state, ',')) {
                    if (state[state.length() - 1] == '}')
                        state.pop_back();
                    if (state[0] == '{')
                        state.erase(0, 1);
                    while (state.back() == ' ')
                        state.pop_back();
                    while (state[0] == ' ')
                        state.erase(0, 1);
                    Q.insert(state);
                    // std::cerr << state << '\n';
                }
            } else if (line[1] == 'S') {
                int i = 0;
                for (; line[i] != '{'; i++)
                    ;
                line = line.substr(i + 1, line.size() - 2 - i);
                std::string symbol;
                std::stringstream ss(line);
                while (std::getline(ss, symbol, ',')) {
                    while (symbol.back() == ' ')
                        symbol.pop_back();
                    while (symbol[0] == ' ')
                        symbol.erase(0, 1);
                    S.insert(symbol[0]);
                }
            } else if (line[1] == 'G') {
                int i = 0;
                for (; line[i] != '{'; i++)
                    ;
                line = line.substr(i + 1, line.size() - 2 - i);
                std::string symbol;
                std::stringstream ss(line);
                while (std::getline(ss, symbol, ',')) {
                    while (symbol.back() == ' ')
                        symbol.pop_back();
                    while (symbol[0] == ' ')
                        symbol.erase(0, 1);
                    G.insert(symbol[0]);
                }
            } else if (line[1] == 'F') {
                int i = 0;
                for (; line[i] != '{'; i++)
                    ;
                line = line.substr(i + 1, line.length() - 2 - i);
                std::string state;
                std::stringstream ss(line);
                while (std::getline(ss, state, ',')) {
                    if (state[state.length() - 1] == '}')
                        state.pop_back();
                    if (state[0] == '{')
                        state.erase(0, 1);
                    while (state.back() == ' ')
                        state.pop_back();
                    while (state[0] == ' ')
                        state.erase(0, 1);
                    F.insert(state);
                }
            } else if (line[1] == 'q' and line[2] == '0') {
                q0 = line.substr(6, line.length() - 1 - 5);
            } else if (line[1] == 'B') {
                Bsym = line[5];
            } else if (line[1] == 'N') {
                N = str2int(line.substr(5, line.length() - 1 - 4));
            }
        } else {
            line = pre_handle(line);
            // std::cerr << line << "\n";
            if (!check_func(line)) {
                std::cerr << "syntax error\n"; // func\n";
                // std::cerr << line << "\n";
                //   std::vector<std::string> func;
                //   std::string word;
                //   std::stringstream ss(line);
                //   while (std::getline(ss, word, ' ')) {
                //      std::cerr << word << "\n";
                //  }
                return 0;
            }
            std::vector<std::string> func;
            std::string word;
            std::stringstream ss(line);
            while (std::getline(ss, word, ' ')) {
                func.push_back(word);
            }
            turningMachine.add_func(func[0], func[1], func[4], func[2],
                                    func[3]);
        }
    }
    if (sets < 7) {
        std::cerr << "syntax error\n";
        return 0;
    }
    turningMachine.init(Q, S, G, F, N, q0, Bsym);
    fin.close();
    return 1;
}