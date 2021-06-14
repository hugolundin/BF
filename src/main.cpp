#include <string>
#include <iostream>

#include "brainfuck.h"

int main(int argc, char const *argv[])
{
    Brainfuck bf("+++++++[>>>>>>>>>>+++++++");

    bf.run();
    std::cout << bf << std::endl;

    return 0;
}
