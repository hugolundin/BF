#pragma once

#include <map>
#include <array>
#include <string>

#define TOKEN_MOVE_RIGHT '>'
#define TOKEN_MOVE_LEFT '<'
#define TOKEN_INCREMENT '+'
#define TOKEN_DECREMENT '-'
#define TOKEN_OUTPUT '.'
#define TOKEN_INPUT ','
#define TOKEN_JUMP_IF_ZERO '['
#define TOKEN_JUMP_IF_NOT_ZERO ']'

const int BF_INF_CYCLES = -1;
const int BF_TAPE_SIZE = 256;
const std::string BF_VALID_TOKENS("><+-.,[]");

class Brainfuck {
    public:
        explicit Brainfuck(std::string tokens, int max_cycles=BF_INF_CYCLES);
        ~Brainfuck();
        
        void step();
        void run();
        bool finished();

        friend std::ostream& operator<<(std::ostream&, const Brainfuck&);

    private:
        int m_pc;
        int m_cycles;
        int m_pointer;
        int m_max_cycles;
        std::string m_tokens;
        std::map<int, int> m_jumps;
        std::array<int, BF_TAPE_SIZE> m_tape;

        void move_right();
        void move_left();
        void increment();
        void decrement();
        void print();
        void read();
        void jump_if_zero();
        void jump_if_not_zero();
};
