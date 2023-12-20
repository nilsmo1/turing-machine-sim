#pragma once

#include <iostream>
#include <map>
#include <vector>
#include <tuple>
#include <string>

typedef std::tuple<std::string, char>          K_TRANSITION;
typedef std::tuple<char, char, std::string>    V_TRANSITION;
typedef std::tuple<K_TRANSITION, V_TRANSITION> SPLIT;

class TuringMachine {
private:
    std::map<K_TRANSITION, V_TRANSITION> m_transition_function;
    std::vector<char> m_tape;
    std::vector<char> m_input_tape;
    std::string m_current_state;
    int m_tape_head{};
    int m_tape_length{};
    char m_current_symbol;
    std::string m_file_name;
    bool m_running;

public:
    TuringMachine(std::string file_name) { m_file_name = file_name; };
    ~TuringMachine() { 
        m_transition_function.clear();
        std::cout << "\x1B[?25h\n";
    };

    void transition_from_stringstream(std::string);
    void read_transition_function();
    void read_tape(std::string);
    V_TRANSITION get_transition();
    void move_tape_head(char);
    void get_tape_symbol();
    void write_tape(char);
    void display_tape();
    void display_info();
    std::vector<char> get_input_tape();
    std::vector<char> get_tape();
    void step();
    void run(bool);
};
