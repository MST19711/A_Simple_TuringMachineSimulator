#include <iostream>
#include <set>
#include <string>

#ifndef TAPE
#define TAPE
#define B 32
int get_int_strlen(int x);
class TapeNode {
  public:
    TapeNode *precursor() { return this->_precursor; }
    TapeNode *successor() { return this->_successor; }
    void set_precursor(TapeNode *new_precursor) {
        this->_precursor = new_precursor;
    }
    void set_successor(TapeNode *new_successor) {
        this->_successor = new_successor;
    }
    char read() { return this->_symble; };
    void write(char sym) { this->_symble = sym; }
    TapeNode(char init_sym, TapeNode *P, TapeNode *S, int init_index) {
        this->_symble = init_sym;
        _precursor = P, _successor = S;
        _index = init_index;
    }
    TapeNode(TapeNode *P, TapeNode *S) {
        this->_symble = B;
        _precursor = P, _successor = S;
    }
    int index() { return _index; }

  private:
    char _symble;
    TapeNode *_precursor, *_successor;
    int _index;
};

class Tape {
  public:
    Tape(const std::set<char> &G, const std::string &init_tape, char BSym);
    Tape() {}
    char read();
    void write(char new_sym);
    void move_left();
    void move_right();
    bool set_tape(const std::string &tar_tape);
    bool print(int tape_id, int dis);
    bool print_tape_str();
    void init(const std::set<char> &G, const std::string &init_tape, char BSym);
    ~Tape();

  private:
    void _add_node_left(char new_sym);
    void _add_node_right(char new_sym);
    TapeNode *_left, *_right, *_now;
    std::set<char> _G;
    char _BSym;
};
#endif