#include <sstream>
#include <iostream>
#include <stdexcept>
#include <utility>

#include "brainfuck.h"

Brainfuck::Brainfuck(std::string tokens):
    m_pointer(0), m_pc(0), m_tokens(std::move(tokens))
{
    m_tape.fill(0);
}

Brainfuck::~Brainfuck() = default;

void Brainfuck::run()
{
    while (!finished()) {
        switch (m_tokens[m_pc]) {
            case '>':
                move_right();
                break;
            case '<':
                move_left();
                break;
            case '+':
                increment();
                break;
            case '-':
                decrement();
                break;
            case '.':
                print();
                break;
            case ',':
                read();
                break;
            case '[':
                jump_if_zero();
                break;
            case ']':
                jump_if_not_zero();
                break;
            default: {
                std::stringstream ss;
                ss << "unknown token: " << "'" << m_tokens[m_pc] << "'";
                throw std::runtime_error(ss.str());
            }
        }

        m_pc++;
    }
}

void Brainfuck::move_right()
{
    m_pointer++;
}

void Brainfuck::move_left()
{
    m_pointer--;
}

void Brainfuck::increment()
{
    m_tape[m_pointer]++;
}

void Brainfuck::decrement()
{
    m_tape[m_pointer]--;
}

void Brainfuck::print()
{
    putchar(m_tape[m_pointer]);
}

void Brainfuck::read()
{
    std::cout << "> ";
    m_tape[m_pointer] = getchar();
}

void Brainfuck::jump_if_zero()
{
    if (m_tape[m_pointer] == 0) {
        proceed_until(']', true);
    }
}

void Brainfuck::jump_if_not_zero()
{
    if (m_tape[m_pointer] != 0) {
        proceed_until('[', false);
    }
}

std::ostream& operator<<(std::ostream& out, const Brainfuck& b)
{
    out << "m_pointer = " << b.m_pointer << std::endl;
    out << "[";

    std::string delimiter;
    for (int i = 0; i < TAPE_SIZE; i++) {
        out << delimiter << b.m_tape[i];
        delimiter = ", ";
    }

    out << "]";
    return out;
}

void Brainfuck::proceed_until(char c, bool direction)
{
    while (!finished() && !match(c)) {
        m_pc += direction ? 1 : -1;
    }
}

bool Brainfuck::finished() {
    return m_pc >= m_tokens.size();
}

bool Brainfuck::match(char c) {
    return c == m_tokens[m_pc];
}

