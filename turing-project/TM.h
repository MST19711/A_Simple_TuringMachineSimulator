#include "tape.h"
#include <iostream>
#include <map>
#include <set>
#include <tuple>
#include <vector>

#ifndef TM
#define TM
struct FuncOut {
    std::string new_sym, new_state, dir;
};
struct tape_funcout {
    std::string tapes_sym;
    FuncOut fout;
};
class TuringMachine {
  public:
    TuringMachine(std::set<std::string> _Q, std::set<char> _S,
                  std::set<char> _G, std::set<std::string> _F, int N,
                  std::string q0, char bsym)
        : _Q(_Q), _S(_S), _G(_G), _F(_F), _N(N), _state(q0), _BSym(bsym) {
        for (int i = 0; i < N; i++) {
            _Tapes.push_back(new Tape(_G, "", _BSym));
        }
        _stop = false;
        _meet_final = false;
        _step = 0;
    }
    TuringMachine() {
        _meet_final = false;
        _stop = false, _step = 0;
    }
    bool init(std::set<std::string> Q, std::set<char> S, std::set<char> G,
              std::set<std::string> F, int N, std::string q0, char bsym) {
        _Q = Q, _S = S, _G = G, _F = F, _N = N, _state = q0, _BSym = bsym;
        while (!_Tapes.empty())
            _Tapes.pop_back();
        for (int i = 0; i < N; i++) {
            _Tapes.push_back(new Tape(_G, "", _BSym));
        }
        _stop = false;
        _meet_final = false;
        _step = 0;
        return 1;
    }
    bool add_func(std::string q, std::string t, std::string new_q,
                  std::string new_sym, std::string dir);
    int go_next_step();
    bool print_status();
    bool set_first_tape(const std::string &tape);
    const bool is_accept();
    bool print_result();
    bool print_V_result();
    const std::set<char> &Tape_symbolset() { return _S; }
    void test_output() { std::cout << _BSym; }
    ~TuringMachine();

  private:
    std::vector<Tape *> _Tapes;
    std::map<std::string, std::vector<tape_funcout>> _delta;
    int _N;
    std::set<std::string> _Q, _F;
    std::set<char> _S, _G;
    std::string _state;
    bool _stop;
    char _BSym;
    int _step;
    bool _meet_final;
};
bool match(std::string p, std::string x);
#endif