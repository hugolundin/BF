#pragma once

#include <array>
#include <string>

const int TAPE_SIZE = 256;

class Brainfuck {
    public:
        explicit Brainfuck(std::string);
        ~Brainfuck();
        void run();
        friend std::ostream& operator<<(std::ostream&, const Brainfuck&);

    private:
        int m_pc;
        int m_pointer;
        std::string m_tokens;
        std::array<int, TAPE_SIZE> m_tape {};

        bool finished();
        bool match(char);
        void proceed_until(char, bool);

        void move_right();
        void move_left();
        void increment();
        void decrement();
        void print();
        void read();
        void jump_if_zero();
        void jump_if_not_zero();
};
