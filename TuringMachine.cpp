#include "TuringMachine.h"
#include <fstream>
#include <cctype>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <tuple>
#include <sstream>
#include <vector>


void print_tuple(K_TRANSITION t) {
    std::cout <<
        std::get<0>(t) << " " <<
        std::get<1>(t);
}

void print_tuple(V_TRANSITION t) {
    std::cout <<
        std::get<0>(t) << " " <<
        std::get<1>(t) << " " <<
        std::get<2>(t);

}

void print_map(std::map<K_TRANSITION, V_TRANSITION> m) {
    for (auto &p : m) {
        print_tuple(p.first);
        std::cout << " ";
        print_tuple(p.second);
    }
    std::cout << '\n';
}

void TuringMachine::transition_from_stringstream(std::string line) {
    std::stringstream tmp(line);
    std::string part;
    std::vector<std::string> parts;
    while (tmp >> part) {
        if (part == "_initial_state_") {
            tmp >> part;
            m_current_state = part;
            return;
        }
        parts.push_back(part);
    }
    if (parts.size() != 5) throw std::runtime_error("State does not contain 5 components!");
    K_TRANSITION k_transition = std::make_tuple(parts[0], parts[1][0]);
    V_TRANSITION v_transition = std::make_tuple(parts[2][0], toupper(parts[3][0]), parts[4]);
    m_transition_function[k_transition] = v_transition;
}

void TuringMachine::read_transition_function() {
    std::ifstream input_file(m_file_name);
    std::string line;
    if (input_file.is_open()) {
        while (std::getline(input_file, line))
            transition_from_stringstream(line);
        input_file.close();
    }
}

void TuringMachine::read_tape(std::string sequence) {
    for (char c : sequence) {
        m_tape.push_back(c);
        m_input_tape.push_back(c);
        m_tape_length++;
    }
}

V_TRANSITION TuringMachine::get_transition() {
    K_TRANSITION k_transition = std::make_tuple(m_current_state, m_current_symbol);
    try {
        V_TRANSITION transition = m_transition_function.at(k_transition);
        std::string s = std::get<2>(transition);
        return transition;
    } catch (std::out_of_range const&) {
        return std::make_tuple('.', '.', "halt");
    }
}

void TuringMachine::move_tape_head(char direction) {
    switch (toupper(direction)) {
        case 'R':
            if (m_tape_head == m_tape_length)
                m_tape.push_back('_');
            m_tape_head++; break;
        case 'L':
            if (m_tape_head == 0)
                throw std::runtime_error("Moving tape head left at index 0!");
            m_tape_head--; break;
        case '.': return;
        default:
            std::string error_message = "Undefined direction ";
            error_message.push_back(direction);
            throw std::runtime_error(error_message);
    }
}

void TuringMachine::get_tape_symbol() {
    m_current_symbol = m_tape[m_tape_head];
}

void TuringMachine::write_tape(char symbol) {
    m_tape[m_tape_head] = symbol;
}

void TuringMachine::display_tape() {
    std::cout << "Tape ";
    for (int i = 0; i < m_tape_length; ++i) {
        if (i == m_tape_head) {
            std::cout << "\x1B[4m" << m_tape[i] << "\x1B[0m";
            continue;
        }
        std::cout << m_tape[i];
    } std::cout << '\n';
}

void TuringMachine::display_info() {
    V_TRANSITION v_transition = get_transition();
    std::cout << "\x1B[3A";
    std::cout << "\x1B[0G\e[K";
    std::cout << "State=" << m_current_state << ", Symbol=" << m_current_symbol;
    if (std::get<2>(v_transition).substr(0,4) != "halt") {
        std::cout << ", Transition=";
        print_tuple(v_transition);
    }
    std::cout << "\n\x1B[0G\e[K";
    display_tape();
}


std::vector<char> TuringMachine::get_input_tape() {
    return m_input_tape;
}

std::vector<char> TuringMachine::get_tape() {
    return m_tape;
}


void TuringMachine::step() {
    get_tape_symbol();
    V_TRANSITION v_transition = get_transition();
    display_info();
    char write_symbol = std::get<0>(v_transition);
    char direction = std::get<1>(v_transition);
    m_current_state = std::get<2>(v_transition);
    if (m_current_state.substr(0,4) == "halt") {
        m_running = false;
        std::cout << '\n';
    }
    write_tape(write_symbol);
    move_tape_head(direction);
    std::cout << "\x1B[?25l";
}

void TuringMachine::run(bool run_type) {
    read_transition_function();
    get_tape_symbol();
    m_running = true;
    std::cout << "\n\n\n";
    while (m_running) {
        step();
        if (!m_running)
            break;
        if (!run_type)
            getchar();
        else
         std::cout << '\n';
    } display_info();
}
