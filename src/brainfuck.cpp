#include <sstream>
#include <iostream>
#include <stdexcept>
#include <utility>
#include <stack>

#include "brainfuck.h"

Brainfuck::Brainfuck(std::string tokens):
    m_pointer(0), m_pc(0),
    m_tokens(std::move(tokens)), m_tape(), m_jumps()
{
    m_tape.fill(0);

    int start;
    char current;
    std::stack<int> braces;

    for (int position = 0; position < m_tokens.size(); position++) {
        current = m_tokens[position];

        if (current == TOKEN_JUMP_IF_ZERO) {
            braces.push(position);
        } else if (current == TOKEN_JUMP_IF_NOT_ZERO) {
            start = braces.top();
            braces.pop();
            m_jumps[start] = position;
            m_jumps[position] = start;
        }
    }
}

Brainfuck::~Brainfuck() = default;

void Brainfuck::step()
{
    switch (m_tokens[m_pc]) {
        case TOKEN_MOVE_RIGHT:
            move_right();
            break;
        case TOKEN_MOVE_LEFT:
            move_left();
            break;
        case TOKEN_INCREMENT:
            increment();
            break;
        case TOKEN_DECREMENT:
            decrement();
            break;
        case TOKEN_OUTPUT:
            print();
            break;
        case TOKEN_INPUT:
            read();
            break;
        case TOKEN_JUMP_IF_ZERO:
            jump_if_zero();
            break;
        case TOKEN_JUMP_IF_NOT_ZERO:
            jump_if_not_zero();
            break;
        default:
            break;
    }

    m_pc++;
}

void Brainfuck::run()
{
    while (!finished()) {
        step();
    }
}

bool Brainfuck::finished() {
    return m_pc >= m_tokens.size();
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
        m_pc = m_jumps[m_pc];
    }
}

void Brainfuck::jump_if_not_zero()
{
    if (m_tape[m_pointer] != 0) {
        m_pc = m_jumps[m_pc];
    }
}

std::ostream& operator<<(std::ostream& out, const Brainfuck& b)
{
    out << "m_pointer = " << b.m_pointer << std::endl;
    out << "[";

    std::string delimiter;
    for (int i = 0; i < BF_TAPE_SIZE; i++) {
        out << delimiter << b.m_tape[i];
        delimiter = ", ";
    }

    out << "]";
    return out;
}


