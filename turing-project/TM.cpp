#include "TM.h"
#include "tape.h"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>
bool TuringMachine::add_func(std::string q, std::string t, std::string new_q,
                             std::string new_sym, std::string dir) {
    FuncOut temp;
    tape_funcout new_m;
    temp.dir = dir, temp.new_state = new_q, temp.new_sym = new_sym;
    new_m.fout = temp, new_m.tapes_sym = t;
    _delta[q].push_back(new_m);
    return 1;
}
bool match(std::string p, std::string x) {
    // std::cerr << "cmp  " << p << " : " << x << "\n";
    for (int i = 0; i < std::min(p.length(), x.length()); i++) {
        if (p[i] != '*' and p[i] != x[i]) {
            return 0;
        }
    }
    return 1;
}
bool match_tapesym(std::string p, std::string x, char bsym) {
    // std::cerr << "cmp  " << p << " : " << x << "\n";
    for (int i = 0; i < std::min(p.length(), x.length()); i++) {
        if ((p[i] != '*' and p[i] != x[i]) or (p[i] == '*' and x[i] == bsym)) {
            return 0;
        }
    }
    return 1;
}
int TuringMachine::go_next_step() {
    _step++;
    if (_F.count(_state) > 0)
        _meet_final = true;
    std::string now_tapes;
    for (auto i : this->_Tapes) {
        now_tapes += i->read();
    }
    if (_delta.count(_state) > 0) {
        for (auto i : _delta[_state]) {
            if (match_tapesym(i.tapes_sym, now_tapes, _BSym)) {
                _state = i.fout.new_state;
                for (int j = 0; j < _N; j++) {
                    if (i.fout.new_sym[j] != '*') {
                        _Tapes[j]->write(i.fout.new_sym[j]);
                    }
                    if (i.fout.dir[j] != '*') {
                        if (i.fout.dir[j] == 'l')
                            _Tapes[j]->move_left();
                        else
                            _Tapes[j]->move_right();
                    }
                }
                return 1;
            }
        }
    }
    if (_F.count(_state) > 0)
        _meet_final = true;
    _stop = true;
    _step--;
    return 2;
}

bool TuringMachine::set_first_tape(const std::string &tape) {
    _Tapes[0]->set_tape(tape);
    return 1;
}

const bool TuringMachine::is_accept() {
    // for (auto i : _F)
    //     std::cerr << i << " ";
    // std::cerr << _stop << ", " << _F.count(_state) << "\n";
    return _delta.count(_state) == 0 and (_meet_final or _F.count(_state) > 0);
}

bool TuringMachine::print_status() {
    int dis = std::max(7, 5 + get_int_strlen(_N)) + 2;
    std::cout << "Step" << std::setw(dis - 4) << ": " << _step << std::endl;
    std::cout << "State" << std::setw(dis - 5) << ": " << _state << std::endl;
    std::cout << "Acc" << std::setw(dis - 3) << ": "
              << (this->is_accept() ? "Yes" : "No") << std::endl;
    for (int i = 0; i < _Tapes.size(); i++) {
        _Tapes[i]->print(i, dis);
    }
    std::cout << "---------------------------------------------\n";
    return true;
}

bool TuringMachine::print_result() {
    if (is_accept())
        std::cout << "(ACCEPTED) ";
    else
        std::cout << "(UNACCEPTED) ";
    _Tapes[0]->print_tape_str();
    std::cout << std::endl;
    return true;
}
bool TuringMachine::print_V_result() {
    if (is_accept())
        std::cout << "ACCEPTED\nResult: ";
    else
        std::cout << "UNACCEPTED\nResult: ";
    _Tapes[0]->print_tape_str();
    std::cout << std::endl << "==================== END ====================\n";
    return true;
}

TuringMachine::~TuringMachine() {
    while (!_Tapes.empty()) {
        delete _Tapes.back();
        _Tapes.pop_back();
    }
}
