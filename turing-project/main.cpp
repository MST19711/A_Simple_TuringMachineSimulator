#include "TM.h"
#include "TMreader.h"
#include "gramma_checker.h"
#include "output.h"
#include "tape.h"

#include <iostream>
using namespace std;
bool V_mode = false;
int main(int argc, char *argv[]) {
    std::string tm_path = "\0";
    for (int i = 0; i < argc; i++) {
        if (match(std::string(argv[i]), "-v") or
            match(std::string(argv[i]), "--verbose"))
            V_mode = true;
        else if (match(std::string(argv[i]), "-h") or
                 match(std::string(argv[i]), "--help"))
            print_help();
        else if (match(".tm", std::string(argv[i]).substr(
                                  std::string(argv[i]).length() - 3,
                                  std::string(argv[i]).length() - 1))) {
            tm_path = std::string(argv[i]);
            break;
        }
    }
    if (tm_path == "\0") {
        std::cerr << "no tm_path\n";
        return 0;
    }
    TuringMachine Scherzo;
    bool try_readTM = read_TM(tm_path, Scherzo);
    if (not try_readTM) {
        return 1;
    }
    int first_invalidnote =
        check_input(Scherzo.Tape_symbolset(), argv[argc - 1]);
    if (V_mode)
        std::cout << "Input: " << argv[argc - 1] << std::endl;
    if (first_invalidnote != -1) {
        if (V_mode)
            gramma_error(first_invalidnote, argv[argc - 1]);
        else
            std::cerr << "illegal input string\n";
        return 1;
    }
    if (V_mode)
        gramma_noerror(argv[argc - 1]);
    Scherzo.set_first_tape(argv[argc - 1]);
    int step_result = 0;
    while (step_result != 2) {
        if (V_mode)
            Scherzo.print_status();
        step_result = Scherzo.go_next_step();
    }
    if (V_mode) {
        Scherzo.print_V_result();
    } else {
        Scherzo.print_result();
    }
    return 0;
}