#include "tape.h"
#include <iomanip>
#include <iostream>
#include <set>
#include <string>

int get_int_strlen(int x) {
    if (x == 0)
        return 1;
    int ret = 0;
    while (x) {
        ret++, x /= 10;
    }
    return ret;
}

void Tape::_add_node_left(char new_sym) {
    TapeNode *new_node =
        new TapeNode(new_sym, nullptr, nullptr, this->_left->index() - 1);
    this->_left->set_precursor(new_node);
    new_node->set_successor(this->_left);
    this->_left = new_node;
}
void Tape::_add_node_right(char new_sym) {
    TapeNode *new_node =
        new TapeNode(new_sym, nullptr, nullptr, this->_right->index() + 1);
    this->_right->set_successor(new_node);
    new_node->set_precursor(this->_right);
    this->_right = new_node;
}
void Tape::init(const std::set<char> &G, const std::string &init_tape,
                char BSym) {
    this->_BSym = BSym;
    this->_G = G;
    TapeNode *first_node;
    if (init_tape.length() == 0) {
        first_node = new TapeNode(_BSym, nullptr, nullptr, 0);
    } else {
        first_node = new TapeNode(init_tape[0], nullptr, nullptr, 0);
    }
    this->_now = first_node;
    this->_left = this->_right = first_node;
    if (init_tape.length() > 1) {
        for (int i = 1; i < init_tape.length(); i++) {
            this->_add_node_right(init_tape[i]);
        }
    }
}
Tape::Tape(const std::set<char> &G, const std::string &init_tape, char BSym) {
    this->_BSym = BSym;
    this->_G = G;
    TapeNode *first_node;
    if (init_tape.length() == 0) {
        first_node = new TapeNode(_BSym, nullptr, nullptr, 0);
    } else {
        first_node = new TapeNode(init_tape[0], nullptr, nullptr, 0);
    }
    this->_now = first_node;
    this->_left = this->_right = first_node;
    if (init_tape.length() > 1) {
        for (int i = 1; i < init_tape.length(); i++) {
            this->_add_node_right(init_tape[i]);
        }
    }
}
char Tape::read() { return this->_now->read(); }
void Tape::write(char new_sym) { this->_now->write(new_sym); }
void Tape::move_left() {
    if (this->_now->precursor() == nullptr) {
        this->_add_node_left(_BSym);
    }
    this->_now = this->_now->precursor();
}
void Tape::move_right() {
    if (this->_now->successor() == nullptr) {
        this->_add_node_right(_BSym);
    }
    this->_now = this->_now->successor();
}

Tape::~Tape() {
    while (this->_left != nullptr) {
        TapeNode *tnow = this->_left;
        this->_left = this->_left->successor();
        delete tnow;
    }
}
bool Tape::set_tape(const std::string &tar_tape) {
    this->_left = this->_right = nullptr;
    TapeNode *first_node;
    if (tar_tape.length() == 0) {
        first_node = new TapeNode(_BSym, nullptr, nullptr, 0);
    } else {
        first_node = new TapeNode(tar_tape[0], nullptr, nullptr, 0);
    }
    this->_now = first_node;
    this->_left = this->_right = first_node;
    for (int i = 1; i < tar_tape.length(); i++) {
        this->_add_node_right(tar_tape[i]);
    }
    return 1;
}

bool Tape::print(int tape_id, int dis) {
    std::cout << "Index" << tape_id
              << std::setw(dis - get_int_strlen(tape_id) - 5) << ": ";
    int i = 0;

    TapeNode *ptr = this->_left, *end = this->_right;
    while (end->read() == _BSym and end != _now)
        end = end->precursor();
    if (end == _now or end != nullptr)
        end = end->successor();
    while (ptr->read() == _BSym and ptr != _now)
        ptr = ptr->successor();
    while (ptr->successor() != nullptr and ptr != end) {
        std::cout << std::abs(ptr->index()) << " ";
        ptr = ptr->successor();
    }
    if (ptr != end) {
        std::cout << std::abs(ptr->index()) << std::endl;
    } else {
        std::cout << "\n";
    }

    ptr = this->_left;
    while (ptr->read() == _BSym and ptr != _now)
        ptr = ptr->successor();
    std::cout << "Tape" << tape_id
              << std::setw(dis - get_int_strlen(tape_id) - 4) << ": ";
    while (ptr->successor() != nullptr and ptr != end) {
        if (ptr->read() == ' ' or ptr->read() == _BSym) {
            std::cout << "_";
        } else {
            std::cout << ptr->read();
        }
        for (int j = 0; j < get_int_strlen(std::abs(ptr->index())); j++)
            std::cout << " ";
        ptr = ptr->successor();
    }
    if (ptr != end) {
        if (ptr->read() == ' ' or ptr->read() == _BSym) {
            std::cout << "_";
        } else {
            std::cout << ptr->read();
        }
    }
    std::cout << std::endl;

    ptr = this->_left;
    while (ptr->read() == _BSym and ptr != _now)
        ptr = ptr->successor();
    std::cout << "Head" << tape_id
              << std::setw(dis - get_int_strlen(tape_id) - 4) << ": ";
    while (ptr != nullptr and ptr != end) {
        if (ptr == this->_now) {
            std::cout << "^\n";
            break;
        }
        for (int j = 0; j < get_int_strlen(std::abs(ptr->index())); j++)
            std::cout << " ";
        std::cout << " ";
        ptr = ptr->successor();
    }
    return 1;
}
bool Tape::print_tape_str() {
    TapeNode *ptr = this->_left, *end = this->_right;
    while (ptr != nullptr and ptr->read() == _BSym)
        ptr = ptr->successor();
    while (end != nullptr and end->read() == _BSym)
        end = end->precursor();
    if (end != nullptr)
        end = end->successor();
    while (ptr != nullptr and ptr != end) {
        if (ptr->read() == ' ' or ptr->read() == _BSym) {
            std::cout << "_";
        } else {
            std::cout << ptr->read();
        }
        ptr = ptr->successor();
    }
    return true;
}